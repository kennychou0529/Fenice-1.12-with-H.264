
#include <string.h>
#include <stdlib.h>

#include <fenice/utils.h>
#include <fenice/rtsp.h>

#if HAVE_ALLOCA_H
#define my_alloca(x) alloca(x)
#define my_free(x)
#else
#define my_alloca(x) malloc(x)
#define my_free(x) free(x)
#endif

//! \return 0 if the URL is valid, 1 if the URL is not valid, -1 on internal error (some buffer too small)
int parse_url(
		const char *url,
		char *server,
		size_t server_len,
		unsigned short *port,
		char *file_name,
		size_t file_name_len)
// Note: this routine comes from OMS
{
	/* expects format '[rtsp://server[:port/]]filename' */

	int not_valid_url = URL_BAD; // 1;
	/* copy url */
	char *full = my_alloca(strlen(url) + 1);

	strcpy(full, url);
	if (strncmp(full, "rtsp://", 7) == 0) {
		char *token;
		int has_port = 0;
		/* BEGIN Altered by Ed Hogan, Trusted Info. Sys. Inc. */
		/* Need to look to see if it has a port on the first host or not. */
		char *aSubStr = my_alloca(strlen(url) + 1);
		strcpy(aSubStr, &full[7]);
		if (strchr(aSubStr, '/')) {
			int len = 0;
			unsigned short i = 0;
			char *end_ptr;
			end_ptr = strchr(aSubStr, '/');
			len = end_ptr - aSubStr;
			for (; (i < strlen(url)); i++)
				aSubStr[i] = 0;
			strncpy(aSubStr, &full[7], len);
		}
		if (strchr(aSubStr, ':'))
			has_port = 1;
		my_free(aSubStr);
		/* END   Altered by Ed Hogan, Trusted Info. Sys. Inc. */

		token = strtok(&full[7], " :/\t\n");
		if (token) {
			strncpy(server, token, server_len);
			if (server[server_len - 1]) {
				my_free(full);
				return URL_ERROR; // -1;	// internal error
			}
			if (has_port) {
				char *port_str = strtok(&full[strlen(server) + 7 + 1], " /\t\n");
				if (port_str)
					*port = (unsigned short) atol(port_str);
				else
					*port = FENICE_RTSP_PORT_DEFAULT;
			} else
				*port = FENICE_RTSP_PORT_DEFAULT;
			/* don't require a file name */
			not_valid_url = URL_OK; // 0;
			token = strtok(NULL, " ");
			if (token) {
				strncpy(file_name, token, file_name_len);
				if (file_name[file_name_len - 1]) {
					my_free(full);
					return URL_ERROR; // -1;	// internal error
				}
			} else
				file_name[0] = '\0';
		}
	} else {
		/* try just to extract a file name */
		char *token = strtok(full, " \t\n");
		if (token) {
			strncpy(file_name, token, file_name_len);
			if (file_name[file_name_len - 1]) {
				my_free(full);
				return URL_ERROR; // -1;	// internal error
			}
			server[0] = '\0';
			not_valid_url = 0;
		}
	}
	my_free(full);

	return not_valid_url;
}
