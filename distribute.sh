rm -r ./distributables/linux/*

cp ./main ./distributables/linux/skala

cp -r ./assets ./distributables/linux/assets

cp -r ./shaders ./distributables/linux/shaders

cp ./saveData-origin.txt ./distributables/linux/saveData-origin.txt

cp ./distributables/linux/saveData-origin.txt ./distributables/linux/saveData.txt

cp ./settings-origin.txt ./distributables/linux/settings-origin.txt

cp ./distributables/linux/settings-origin.txt ./distributables/linux/settings.txt

cd distributables

rm ./linux.zip

zip -r ./linux.zip ./linux/

cd ..
