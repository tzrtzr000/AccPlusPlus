# https://askubuntu.com/questions/618663/creating-a-folder-based-on-a-portion-of-a-file-name
for file in *.cpp; do
    base=${file%.cpp}
    g++ -std=c++11 -ggdb -pg ${file} -o "${base}.out" `pkg-config --cflags --libs opencv4` 
    rm -rf  "./${base}"
    mkdir -p "./${base}"
    mv "${base}.out" "./$base" 
    # mv -iv "gmon.out" "./$base" 
done

echo "Compile finished!"