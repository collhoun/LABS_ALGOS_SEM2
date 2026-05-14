
set -euo pipefail

# значения по умолчангию
PREFIX=""
MIN_SIZE=0
MAX_SIZE=""
DIRECTORY=""
RECURSIVE=false
DRY_RUN=false

# цвета для красивого вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

# вывод справочной информации
usage() {
    cat <<EOF
${CYAN}Использование:${RESET}
  $(basename "$0") [OPTIONS] <директория>

${CYAN}Опции:${RESET}
  -p, --prefix <PREFIX>   Префикс имени файла (обязательно)
  -m, --min <BYTES>       Минимальный размер в байтах, включительно (по умолчанию: 0)
  -M, --max <BYTES>       Максимальный размер в байтах, включительно (обязательно)
  -r, --recursive         Рекурсивный поиск в поддиректориях
  -d, --dry-run           Показать файлы без фактического удаления
  -h, --help              Показать эту справку

${CYAN}Примеры:${RESET}
  $(basename "$0") -p "tmp_" -m 1024 -M 1048576 /var/data
  $(basename "$0") -p "log_" -M 5000 -r --dry-run /home/user
EOF
}


parse_args() {
    while [[ $# -gt 0 ]]; do
        case "$1" in
            -p|--prefix)    PREFIX="$2";    shift 2 ;;
            -m|--min)       MIN_SIZE="$2";  shift 2 ;;
            -M|--max)       MAX_SIZE="$2";  shift 2 ;;
            -r|--recursive) RECURSIVE=true; shift   ;;
            -d|--dry-run)   DRY_RUN=true;   shift   ;;
            -h|--help)      usage; exit 0            ;;
            -*)
                echo -e "${RED}Ошибка: неизвестный параметр '$1'${RESET}" >&2
                usage; exit 1
                ;;
            *)
                DIRECTORY="$1"; shift ;;
        esac
    done
}

validate() {
    local errors=0

    if [[ -z "$PREFIX" ]]; then
        echo -e "${RED}Ошибка: префикс (-p) не указан.${RESET}" >&2
        ((++errors))
    fi

    if [[ -z "$MAX_SIZE" ]]; then
        echo -e "${RED}Ошибка: максимальный размер (-M) не указан.${RESET}" >&2
        ((++errors))
    fi

    if [[ -z "$DIRECTORY" ]]; then
        echo -e "${RED}Ошибка: директория не указана.${RESET}" >&2
        ((++errors))
    elif [[ ! -d "$DIRECTORY" ]]; then
        echo -e "${RED}Ошибка: директория '$DIRECTORY' не существует.${RESET}" >&2
        ((++errors))
    fi

    if ! [[ "$MIN_SIZE" =~ ^[0-9]+$ ]]; then
        echo -e "${RED}Ошибка: минимальный размер должен быть неотрицательным целым числом.${RESET}" >&2
        ((++errors))
    fi

    if [[ -n "$MAX_SIZE" ]] && ! [[ "$MAX_SIZE" =~ ^[0-9]+$ ]]; then
        echo -e "${RED}Ошибка: максимальный размер должен быть целым числом.${RESET}" >&2
        ((++errors))
    fi

    if [[ -n "$MAX_SIZE" && "$MIN_SIZE" -gt "$MAX_SIZE" ]]; then
        echo -e "${RED}Ошибка: минимальный размер ($MIN_SIZE) больше максимального ($MAX_SIZE).${RESET}" >&2
        ((++errors))
    fi

    [[ $errors -eq 0 ]]
}


main() {
    parse_args "$@"
    validate || exit 1

    local depth_args=(-maxdepth 1)
    $RECURSIVE && depth_args=()

    echo -e "${CYAN}Параметры поиска:${RESET}"
    echo -e "  Директория : ${DIRECTORY}"
    echo -e "  Префикс    : ${PREFIX}"
    echo -e "  Размер     : от ${MIN_SIZE} до ${MAX_SIZE} байт"
    echo -e "  Рекурсия   : $( $RECURSIVE && echo 'да' || echo 'нет' )"
    echo -e "  Режим      : $( $DRY_RUN  && echo "${YELLOW}dry-run (только просмотр)${RESET}" || echo "${RED}реальное удаление${RESET}" )"
    echo ""

    local count=0
    local total_size=0


    while IFS= read -r -d '' file; do
        local size
        if stat --version &>/dev/null 2>&1; then
            # для линуха
            size=$(stat -c '%s' "$file")
        else
            # для яблочников
            size=$(stat -f '%z' "$file")
        fi

        if [[ "$size" -ge "$MIN_SIZE" && "$size" -le "$MAX_SIZE" ]]; then
            if $DRY_RUN; then
                echo -e "  ${YELLOW}[dry-run]${RESET} ${file} (${size} байт)"
            else
                echo -e "  ${RED}Удаляется:${RESET} ${file} (${size} байт)"
                rm -f "$file"
            fi
            ((++count))
            ((total_size += size))
        fi
    done < <(find "$DIRECTORY" "${depth_args[@]}" -type f -name "${PREFIX}*" -print0)

    echo ""
    if [[ $count -eq 0 ]]; then
        echo -e "${YELLOW}Файлы, соответствующие условиям, не найдены.${RESET}"
    else
        local action
        $DRY_RUN && action="Найдено" || action="Удалено"
        echo -e "${GREEN}${action}: ${count} файл(ов), суммарный размер: ${total_size} байт.${RESET}"
    fi
}

main "$@"