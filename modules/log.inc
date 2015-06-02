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
	NONE = 0,
	DEBUG_ = 1,
	INFO = 2,
	WARNING = 4,
	ERROR = 8,
	DEVELOPER = LOG_LEVEL:DEBUG | LOG_LEVEL:INFO | LOG_LEVEL:WARNING | LOG_LEVEL:ERROR,
	PRODUCTION = LOG_LEVEL:INFO | LOG_LEVEL:WARNING | LOG_LEVEL:ERROR
}
new LOG_LEVEL:ActiveLogLevel = DEVELOPER;

forward Log(const message[], LOG_LEVEL:logLevel_);
forward Debug_(const message[], const timestamp[]);
forward Info(const message[], const timestamp[]);
forward Warning(const message[], const timestamp[]);
forward Error(const message[], const timestamp[]);
forward CreateTimestamp();

/**
 * <summary>
 *	Prints the desired message to stdout with a log level dependant prefix.
 *	The resulting message is displayed as: "[Log Level] (hh:mm:ss) message".
 * </summary>
 *
 * <param name="message">
 *	The message to be printed.
 * </param>
 *
 * <param name="logLevel_">
 *	The log level that is being printed.
 * </param>
 */
stock Log(const message[], LOG_LEVEL:logLevel_)
{
	if (logLevel_ & ActiveLogLevel == logLevel_)
	{
		switch (logLevel_)
		{
			case DEBUG_: Debug_(message, CreateTimestamp());
			case INFO: Info(message, CreateTimestamp());
			case WARNING: Warning(message, CreateTimestamp());
			case ERROR: Error(message, CreateTimestamp());
		}
	}
}

/**
 * <summary>
 *	Prints desired mesage with debug prefix and current timestamp as hh:mm:ss.
 * </summary>
 *
 * <param name="message">
 *	The message to be printed.
 * </param>
 *
 * <param name="timestamp">
 *	Current timestamp.
 * </param>
 */
stock Debug_(const message[], const timestamp[])
{
	printf("[DEBUG] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with info prefix and current timestamp as hh:mm:ss.
 * </summary>
 *
 * <param name="message">
 *	The message to be printed.
 * </param>
 *
 * <param name="timestamp">
 *	Current timestamp.
 * </param>
 */
stock Info(const message[], const timestamp[])
{
	printf("[INFO] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with warning prefix and current timestamp as hh:mm:ss.
 * </summary>
 *
 * <param name="message">
 *	The message to be printed.
 * </param>
 *
 * <param name="timestamp">
 *	Current timestamp.
 * </param>
 */
stock Warning(const message[], const timestamp[])
{
	printf("[WARNING] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	Prints desired mesage with error prefix and current timestamp as hh:mm:ss.
 * </summary>
 *
 * <param name="message">
 *	The message to be printed.
 * </param>
 *
 * <param name="timestamp">
 *	Current timestamp.
 * </param>
 */
stock Error(const message[], const timestamp[])
{
	printf("[ERROR] (%s) %s", timestamp, message);
}

/**
 * <summary>
 *	This function creates a 24H timestamp formatted as hh:mm:ss.
 * </summary>
 *
 * <returns>
 *	Timestamp string formatted as hh:mm:ss.
 * </returns>
 */
stock CreateTimestamp()
{
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	
	new timestamp[10];
	format(timestamp, sizeof(timestamp), "%02d:%02d:%02d", hours, minutes, seconds);
	
	return timestamp;
}
 