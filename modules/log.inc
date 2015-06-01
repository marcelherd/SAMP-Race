/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/
 
/**
 * This module defines a common logging interface.
 */
 
 enum LOG_LEVEL
 {
	DEBUG_ = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3
 }
 
 forward log(const message[], LOG_LEVEL:logLevel_);
 forward debug_(const message[], const timestamp[]);
 forward info(const message[], const timestamp[]);
 forward warning(const message[], const timestamp[]);
 forward error(const message[], const timestamp[]);
 
 stock log(const message[], LOG_LEVEL:logLevel_)
 {
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	new timestamp[10];
	format(timestamp, sizeof(timestamp), "%i:%i:%i", hours, minutes, seconds);
	
	switch (logLevel_)
	{
		case DEBUG_: debug_(message, timestamp);
		case INFO: info(message, timestamp);
		case WARNING: warning(message, timestamp);
		case ERROR: error(message, timestamp);
	}
 }
 
 stock debug_(const message[], const timestamp[])
 {
	printf("[DEBUG] (%s) %s", timestamp, message);
 }
 
 stock info(const message[], const timestamp[])
 {
	printf("[INFO] (%s) %s", timestamp, message);
 }
 
 stock warning(const message[], const timestamp[])
 {
	printf("[WARNING] (%s) %s", timestamp, message);
 }
 
 stock error(const message[], const timestamp[])
 {
	printf("[ERROR] (%s) %s", timestamp, message);
 }
 