#include "libs.h"
Result save_import(char *data, u64 id, char *loc){
	Result ret = 0;
	FS_Archive save;
	Handle file;
	u64 size = 0;	
	u32 sdPath[3] = {MEDIATYPE_SD, id, id >> 32}, cardPath[3] = {MEDIATYPE_GAME_CARD, id, id >> 32};
	ret = FSUSER_OpenArchive(&save, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, sdPath});
	if(ret != 0){
		ret = FSUSER_OpenArchive(&save, ARCHIVE_USER_SAVEDATA, (FS_Path){PATH_BINARY, 0xC, cardPath});
		if(ret != 0){
			return ret;
		}
	}
	ret = FSUSER_OpenFile (&file, save, fsMakePath(PATH_ASCII, loc), FS_OPEN_READ, 0x0);
	if(ret != 0){
		FSUSER_CloseArchive(save);
		return ret;
	}
	ret = FSFILE_Read(file, NULL, 0x0, data, 20692);
	if(ret != 0){
		FSFILE_Close(file);
		FSUSER_CloseArchive(save);
		return ret;
	}
	FSFILE_Close(file);
	FSUSER_CloseArchive(save);
	return 0;
}