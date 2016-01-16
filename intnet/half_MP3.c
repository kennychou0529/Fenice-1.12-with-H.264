
#include <string.h>

#include <fenice/intnet.h>

int half_MP3(RTP_session * changing_session)
{
	int speed;
	media_entry req, *list, *p;
	SD_descr *matching_descr;

	memset(&req, 0, sizeof(req));

	req.description.flags |= MED_BITRATE;
	req.description.flags |= MED_ENCODING_NAME;
	strcpy(req.description.encoding_name, "MPA");

	enum_media(changing_session->sd_filename, &matching_descr);
	list = matching_descr->me_list;

	speed = changing_session->current_media->description.bitrate / 2;
	p = NULL;
	if (speed == 208000)
		speed = 224000;
	else if (speed == 88000)
		speed = 96000;
	else if (speed == 72000)
		speed = 80000;
	else if (speed == 28000)
		speed = 32000;
	else if (speed == 20000)
		speed = 24000;
	else if (speed == 12000)
		speed = 16000;
	switch (speed) {
	case 224000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 192000;
	case 192000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 176000;
	case 176000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 160000;
	case 160000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 144000;
	case 144000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 128000;
	case 128000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 112000;
	case 112000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 96000;
	case 96000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 80000;
	case 80000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 64000;
	case 64000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 56000;
	case 56000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 48000;
	case 48000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 40000;
	case 40000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 32000;
	case 32000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 24000;
	case 24000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 16000;
	case 16000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		if (p != NULL)
			break;
		speed = 8000;
	case 8000:
		req.description.bitrate = speed;
		p = search_media(&req, list);
		break;
	}
	if (p != NULL)
		return stream_switch(changing_session, p);
	else
		return priority_decrease(changing_session);
}
