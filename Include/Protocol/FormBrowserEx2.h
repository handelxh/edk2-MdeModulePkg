/** @file
  Extension Form Browser Protocol provides the services that can be used to 
  register the different hot keys for the standard Browser actions described in UEFI specification.

Copyright (c) 2011, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under 
the terms and conditions of the BSD License that accompanies this distribution.  
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.                                            

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __FORM_BROWSER_EXTENSION2_H__
#define __FORM_BROWSER_EXTENSION2_H__

#include <Protocol/FormBrowserEx.h>

#define EDKII_FORM_BROWSER_EXTENSION2_PROTOCOL_GUID  \
  { 0xa770c357, 0xb693, 0x4e6d, { 0xa6, 0xcf, 0xd2, 0x1c, 0x72, 0x8e, 0x55, 0xb }}

typedef struct _EDKII_FORM_BROWSER_EXTENSION2_PROTOCOL   EDKII_FORM_BROWSER_EXTENSION2_PROTOCOL;

#define BROWSER_EXTENSION2_VERSION_1  0x10000

/**
  Check whether the browser data has been modified.

  @retval TRUE        Browser data is modified.
  @retval FALSE       No browser data is modified.

**/
typedef
BOOLEAN
(EFIAPI *IS_BROWSER_DATA_MODIFIED) (
  VOID
  );

/**
  Execute the action requested by the Action parameter.

  @param[in] Action     Execute the request action.
  @param[in] DefaultId  The default Id info when need to load default value.

  @retval EFI_SUCCESS              Execute the request action succss.

**/
typedef 
EFI_STATUS 
(EFIAPI *EXECUTE_ACTION) (
  IN UINT32        Action,
  IN UINT16        DefaultId
  );

#define FORM_ENTRY_INFO_SIGNATURE    SIGNATURE_32 ('f', 'e', 'i', 's')

typedef struct {
  UINTN           Signature;
  LIST_ENTRY      Link;

  EFI_HII_HANDLE  HiiHandle;
  EFI_GUID        FormSetGuid;
  UINT16          FormId;
  UINT16          QuestionId;
} FORM_ENTRY_INFO;

#define FORM_ENTRY_INFO_FROM_LINK(a)  CR (a, FORM_ENTRY_INFO, Link, FORM_ENTRY_INFO_SIGNATURE)

struct _EDKII_FORM_BROWSER_EXTENSION2_PROTOCOL {
  ///
  /// Version for protocol future extension.
  ///
  UINT32                    Version;
  SET_SCOPE                 SetScope;
  REGISTER_HOT_KEY          RegisterHotKey;
  REGISTER_EXIT_HANDLER     RegiserExitHandler;
  IS_BROWSER_DATA_MODIFIED  IsBrowserDataModified;
  EXECUTE_ACTION            ExecuteAction;
  ///
  /// A list of type FORMID_INFO is Browser View Form History List.
  ///
  LIST_ENTRY                FormViewHistoryHead;
};

extern EFI_GUID gEdkiiFormBrowserEx2ProtocolGuid;

#endif

