rm ../*.ogg

for file in *.wav
do
	ffmpeg -i $file -acodec libvorbis ../../audio/music/$(basename $file .wav).ogg
done


