case "$1" in
  main)
    ./bin/main datasets/initial datasets/out "$2" "$3"
    ;;
  dice)
    ./bin/dice datasets/out datasets/target tests/results/binarized_datasets/out tests/results/binarized_datasets/target
    ;;
  histogram)
    ./bin/histogram datasets/initial tests/results/histograms/initial
    ./bin/histogram datasets/out tests/results/histograms/out
    ;;
  sse)
    ./bin/sse datasets/initial tests/results/sses/initial "$2" "$3"
    ;;
  *)
    echo "Uso: $0 {main <k> <maxIter> | dice | histogram | sse <maxK> <maxIterations>}"
    exit 1
    ;;
esac