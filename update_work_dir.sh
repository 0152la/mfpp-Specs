if [ $# -ne 1 ]
then
    echo "Expected one argument; new `working_dir` value!"
    exit 1
fi

new_work_dir="working_dir: $1"

for x in ./*/*.yaml
do
    sed -i "s=^working_dir:.*=$new_work_dir=" $x
done
