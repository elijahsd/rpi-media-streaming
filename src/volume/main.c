#include <alsa/asoundlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

int set(int delta) {
	const char card[] = "hw:0";
	const char channel[] = "Line";

	long min, max, volume;

	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;

	snd_mixer_open(&handle, 0);

	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, channel);
	
	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
	snd_mixer_selem_get_playback_volume(elem, 0, &volume);

	volume += delta * ((max - min) / 300);
	if (volume > max) {
		volume = max;
	}
	if (volume < min) {
		volume = min;
	}

	snd_mixer_selem_set_playback_volume_all(elem, volume);

	snd_mixer_close(handle);
}

int main(int argc, char **argv) {

	const char devname[] = "/dev/input/event2";
	int device = open(devname, O_RDONLY);

	struct input_event ev;
	while(1) {
		read(device, &ev, sizeof(ev));
		if (ev.type == 1 && ev.value == 1) {
			switch (ev.code) {
				case 115: // Volume Up
					set(1);
					break;
				case 114: // Volume Down
					set(-1);
					break;
				default:
					break;
			}
		}
	}
	return 0;
}
