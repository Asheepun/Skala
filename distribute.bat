rm -r ./distributables/skala-windows/*

cp ./main.exe ./distributables/skala-windows/skala.exe

cp -r ./assets ./distributables/skala-windows/assets

cp -r ./shaders ./distributables/skala-windows/shaders

cp ./saveData-origin.txt ./distributables/skala-windows/saveData-origin.txt

cp ./distributables/skala-windows/saveData-origin.txt ./distributables/skala-windows/saveData.txt

cp ./settings-origin.txt ./distributables/skala-windows/settings-origin.txt

cp ./distributables/skala-windows/settings-origin.txt ./distributables/skala-windows/settings.txt

cd distributables

rm ./skala-windows.zip

7z a -tzip ./skala-windows.zip ./skala-windows/

cd ..
