
echo "setup-conda.sh: ..."

if [[ "${CONDA_PREFIX:-}" == "" ]]
then
  echo "setup-conda.sh: No CONDA_PREFIX!"
  return 1
fi

export CFLAGS="-I$CONDA_PREFIX/include"
export LIBS="-L$CONDA_PREFIX/lib -Wl,-rpath -Wl,$CONDA_PREFIX/lib -lhistory"

echo "setup-conda.sh: CFLAGS=$CFLAGS"
echo "setup-conda.sh: LIBS=$LIBS"
