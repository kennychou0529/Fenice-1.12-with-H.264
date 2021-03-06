#ifndef _H_LOGCONF_
#define _H_LOGCONF_

/*
 * iLOG3 - log function library written in c
 * author	: calvin
 * email	: calvinwilliams.c@gmail.com
 *
 * Licensed under the LGPL v2.1, see the file LICENSE in base directory.
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "log.h"

/* 函数返回值宏 */ /* function returns value macros */
#define LOGCONF_RETURN_ERROR_CONFIGFILE_NOTFOUND	-51	/* 找不到配置文件 */
#define LOGCONF_RETURN_ERROR_CONFIGFILE_INVALID		-52	/* 配置文件无效 */

/* 读取配置文件，创建日志句柄 */ /* create log handle from config file */
LOG *CreateLogHandleFromConfig( char *config_filename , char *postfix );

/* 风格替换宏 */
#define create_log_handle_from_config		CreateLogHandleFromConfig

#ifdef __cplusplus
}
#endif

#endif
