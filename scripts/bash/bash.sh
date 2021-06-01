for ((i = 1; ; i++))
do
    echo $i
    ./gen.exe $i > test.in
    ./a.exe < test.in > a.out
    ./b.exe < test.in > b.out
    diff -w a.out b.out || break
done