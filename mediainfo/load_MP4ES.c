
#include <stdio.h>

#include <fenice/utils.h>
#include <fenice/mpeg4es.h>

#define FREE_N_RET(x)	do { \
				free(s->header_data); \
		  		free(s); \
		  		return x; \
			} while (0)

int load_MP4ES(media_entry * p)
{

	/*int ret;
	   int data_size=0;
	   int i;
	   char *o;
	   static_MPEG4_video_es *s=NULL;
	 */

	if (!(p->description.flags & MED_PKT_LEN)) {
		if (!(p->description.flags & MED_FRAME_RATE)) {
			return ERR_PARSE;
		}
		p->description.pkt_len =
		    1 / (double) p->description.frame_rate * 1000;
		p->description.flags |= MED_PKT_LEN;
	}
	p->description.delta_mtime = p->description.pkt_len;

	if ((p->description.byte_per_pckt != 0)
	    && (p->description.byte_per_pckt < 261)) {
		printf
		    ("Warning: the max size for MPEG Video packet is smaller than 261 bytes and if a video header\n");
		printf("is greater the max size would be ignored \n");
		printf("Using Default \n");
	}
#if 0
	if ((ret = mediaopen(p)) < 0) {
		return ret;
	}
	s = (static_MPEG4_video_es *) calloc(1, sizeof(static_MPEG4_video_es));
	s->header_data = (char *) calloc(1, 65000);
	if (s == NULL || s->header_data == NULL)
		return ERR_ALLOC;

	if (next_start_code(s->header_data, &data_size, p->fd) < 0)
		FREE_N_RET(ERR_EOF);
	if (read(p->fd, &s->final_byte, 1) < 1)
		FREE_N_RET(ERR_EOF);
	(s->header_data)[data_size] = s->final_byte;
	data_size += 1;

	if (s->final_byte == VOS_START_CODE) {
		ret =
		    parse_visual_object_sequence(s, s->header_data, &data_size,
						 p->fd);
		if (ret != ERR_NOERROR)
			FREE_N_RET(ret);
		if (next_start_code(s->header_data, &data_size, p->fd) < 0)
			FREE_N_RET(ERR_EOF);
		if (read(p->fd, &s->final_byte, 1) < 1)
			FREE_N_RET(ERR_EOF);
		(s->header_data)[data_size] = s->final_byte;
		data_size += 1;
	}
/*	else
		return ERR_PARSE;
*/
	if (s->final_byte == VO_START_CODE) {
		ret = parse_visual_object(s->header_data, &data_size, p->fd);
		if (ret != ERR_NOERROR)
			FREE_N_RET(ret);
		s->final_byte = (s->header_data)[data_size - 1];
	}
/*	else
		return ERR_PARSE;
*/
	if ( /*(s->final_byte >= 0x00) && */ (s->final_byte <= 0x1F)) {
		ret = parse_video_object(s->header_data, &data_size, p->fd);
		if (ret != ERR_NOERROR)
			FREE_N_RET(ret);
		s->final_byte = (s->header_data)[data_size - 1];
	}

	if ((s->final_byte >= 0x20) && (s->final_byte <= 0x2F)) {
		ret =
		    parse_video_object_layer(s, s->header_data, &data_size,
					     p->fd);
		if (ret != ERR_NOERROR)
			FREE_N_RET(ret);
		s->final_byte = (s->header_data)[data_size - 1];
	}

	s->header_data_size = data_size - 4;

	/*o=s->config;
	   for( i = 0; i < data_size-4; ++i )
	   o+=sprintf( o, "%02X", (s->header_data)[i] ) ;

	   strcat(s->config,"\0"); */
	s->fragmented = 0;
	p->stat = (void *) s;
	//fstat(p->fd, &fdstat);
	//if ( !S_ISFIFO(fdstat.st_mode) ) 
	mediaclose(p);

#endif

	return ERR_NOERROR;
}
