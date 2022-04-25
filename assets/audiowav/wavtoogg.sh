rm ../*.ogg

for file in *.wav
do
	ffmpeg -i $file -acodec libvorbis ../audio/$(basename $file .wav).ogg
done


