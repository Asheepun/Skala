rm -r ./distributables/skala-linux/*

cp ./main ./distributables/skala-linux/skala

cp -r ./assets ./distributables/skala-linux/assets

cp -r ./shaders ./distributables/skala-linux/shaders

cp ./saveData-origin.txt ./distributables/skala-linux/saveData-origin.txt

cp ./distributables/skala-linux/saveData-origin.txt ./distributables/skala-linux/saveData.txt

cp ./settings-origin.txt ./distributables/skala-linux/settings-origin.txt

cp ./distributables/skala-linux/settings-origin.txt ./distributables/skala-linux/settings.txt

cd distributables

rm ./skala-linux.zip

zip -r ./skala-linux.zip ./skala-linux/

cd ..
