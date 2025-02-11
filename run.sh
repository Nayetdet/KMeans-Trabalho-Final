#!/bin/bash
# *********************************************************
# * Aluno: João Pedro Moreira Campos de Lima              *
# * Matrícula: 20241045050391                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Isaac da Cunha Cavalcanti Duarte               *
# * Matrícula: 20241045050375                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Josué Rodrigues Avelino                        *
# * Matrícula: 20241045050219                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Orleoncio Maciel                               *
# * Matrícula: 20181045050165                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************

readonly INITIAL_PATH="datasets/initial"
readonly OUT_PATH="datasets/out"
readonly TARGET_PATH="datasets/target"
readonly BINARIZED_OUT_PATH="tests/results/binarized_datasets/out"
readonly BINARIZED_TARGET_PATH="tests/results/binarized_datasets/target"
readonly HISTOGRAMS_INITIAL_PATH="tests/results/histograms/initial"
readonly HISTOGRAMS_OUT_PATH="tests/results/histograms/out"
readonly SSE_PATH="tests/results/sses/initial"

case "$1" in
    main)
        ./bin/"$1" "$INITIAL_PATH" "$OUT_PATH" "$2" "$3"
        ;;
    dice)
        ./bin/"$1" "$OUT_PATH" "$TARGET_PATH" "$BINARIZED_OUT_PATH" "$BINARIZED_TARGET_PATH"
        ;;
    histogram)
        ./bin/"$1" "$INITIAL_PATH" "$HISTOGRAMS_INITIAL_PATH"
        ./bin/"$1" "$OUT_PATH" "$HISTOGRAMS_OUT_PATH"
        ;;
    sse)
        ./bin/"$1" "$INITIAL_PATH" "$SSE_PATH" "$2" "$3"
        ;;
    *)
        echo "Erro: Use "$0" main | dice | histogram | sse"
        exit 1
        ;;
esac
