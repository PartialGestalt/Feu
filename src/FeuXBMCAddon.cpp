#ifndef __FEU_ADDON_C__
#define __FEU_ADDON_C__

#include <stdio.h>

/* Force C linkage for the whole dang file */

extern "C" {

/** ***************************************************************************
 * @brief Register our screensaver
 *
 * @details This function initializes the struct from core to register our
 * entry points.
 *
 * @param pScr -- Pointer to container into which we'll register
 *
 * @returns Nothing
 *
 * @remarks
 * */

void get_addon(struct ScreenSaver *pScr)
{
    /* These are the only required entrypoints */
    pScr->Start = ADDON_Start;
    pScr->Render = ADDON_Render;
    pScr->GetInfo = ADDON_GetInfo;
}

/** ***************************************************************************
 * @brief Instantiation
 *
 * @details XBMC Core calls this to prep initial setup
 *
 * @param hdl -- Handle
 * @param props -- Screen properties
 *
 * @returns Result code indicating success or failure mode
 *
 * @remarks
 * */
ADDON_STATUS ADDON_Create(void *hdl, void *props)
{
    SCR_PROPS *scr = (SCR_PROPS *)props;

    printf("\n[ADDON_Create \"%s\", presets=\"%s\", profile=\"%s\"]",scr->name,scr->presets,scr->profile);fflush(stdout);
    return ADDON_STATUS_NEED_SETTINGS;
}

/** ***************************************************************************
 * @brief Start the addon operation
 *
 * @details This function is called by the XBMC Core when the screensaver has
 * been triggered for operation.
 *
 * @param
 *
 * @returns Result code indicating success or failure mode
 *
 * @remarks
 * */
void ADDON_Start()
{
    printf("\n[ADDON_Start]");fflush(stdout);
    return;
}

/** ***************************************************************************
 * @brief Screensaver rendering tick
 *
 * @details This function is called occasionally by the XBMC core while 
 * the screensaver is active.  Process as a screen tick and propagate to
 * the handler modules
 *
 * @remarks
 * */
void ADDON_Render()
{
    return;
}

/** ***************************************************************************
 * @brief Stop screensaver processing
 *
 * @details This function is called by the XBMC core when the screensaver
 * should stop rendering.
 *
 * @remarks Note the inversion of module ordering.
 * */
void ADDON_Stop()
{
    printf("\n[ADDON_Stop]");fflush(stdout);
    return;
}

void ADDON_Remove()
{
    printf("\n[ADDON_Remove]");fflush(stdout);
}

void ADDON_Destroy()
{
    printf("\n[ADDON_Destroy]");fflush(stdout);
    return;
}

void ADDON_GetInfo(SCR_INFO *info)
{
    printf("[GetInfo]");fflush(stdout);
}

ADDON_STATUS ADDON_GetStatus()
{
    printf("[ADDON_GetStatus]");fflush(stdout);
    return ADDON_STATUS_OK;
}

bool ADDON_HasSettings()
{
    printf("[ADDON_HasSettings]");fflush(stdout);
    return true;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
    printf("[ADDON_GetSettings]");fflush(stdout);
    return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *settingName, const void *settingValue)
{
    printf("[ADDON_SetSetting \"%s\"=\"%s\"]",(char *)settingName,(char *)settingValue);
    return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
    printf("[ADDON_FreeSettings]");fflush(stdout);
}

} /* extern "C" */

#endif /* __FEU_ADDON_C__ */
