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
 
 forward Log(const message[], LOG_LEVEL:logLevel_);
 forward Debug_(const message[], const timestamp[]);
 forward Info(const message[], const timestamp[]);
 forward Warning(const message[], const timestamp[]);
 forward Error(const message[], const timestamp[]);
 forward CreateTimestamp();
 
 stock Log(const message[], LOG_LEVEL:logLevel_)
 {
	switch (logLevel_)
	{
		case DEBUG_: Debug_(message, CreateTimestamp());
		case INFO: Info(message, CreateTimestamp());
		case WARNING: Warning(message, CreateTimestamp());
		case ERROR: Error(message, CreateTimestamp());
	}
 }
 
 stock Debug_(const message[], const timestamp[])
 {
	printf("[DEBUG] (%s) %s", timestamp, message);
 }
 
 stock Info(const message[], const timestamp[])
 {
	printf("[INFO] (%s) %s", timestamp, message);
 }
 
 stock Warning(const message[], const timestamp[])
 {
	printf("[WARNING] (%s) %s", timestamp, message);
 }
 
 stock Error(const message[], const timestamp[])
 {
	printf("[ERROR] (%s) %s", timestamp, message);
 }
 
 stock CreateTimestamp()
 {
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);

	new timestamp[10];
	format(timestamp, sizeof(timestamp), "%02d:%02d:%02d", hours, minutes, seconds);
	
	return timestamp;
 }
 