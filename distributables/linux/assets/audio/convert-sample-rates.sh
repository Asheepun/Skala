for file in ./*.wav ./music/*.wav
do
	echo $file
	sox $file -r 44100 "tmp.wav"
	mv "tmp.wav" $file
done
