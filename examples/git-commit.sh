
gm()
# Git-Commit with Message
{
  local MESSAGE_FILE=$( mktemp )
  readline -d $MESSAGE_FILE \
           -p "Enter commit message: " \
           -H ~/.git-history \
    || return 1
  git commit ${*} --file=$MESSAGE_FILE
  rm $MESSAGE_FILE
}
