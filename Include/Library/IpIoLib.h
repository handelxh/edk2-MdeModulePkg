/** @file
  This library is only intended to be used by UEFI network stack modules.
  It provides the combined IpIo layer on the EFI IP4 Protocol and EFI IP6 protocol.

Copyright (c) 2005 - 2009, Intel Corporation.<BR>
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _IP_IO_H_
#define _IP_IO_H_

#include <Protocol/Ip4.h>
#include <Protocol/Ip6.h>

#include <Library/NetLib.h>

//
// type and code define for ICMP protocol error 
// from IP
//
#define ICMP_TYPE_UNREACH              3
#define ICMP_TYPE_TIMXCEED             11
#define ICMP_TYPE_PARAMPROB            12
#define ICMP_TYPE_SOURCEQUENCH         4

#define ICMP_CODE_UNREACH_NET          0
#define ICMP_CODE_UNREACH_HOST         1
#define ICMP_CODE_UNREACH_PROTOCOL     2
#define ICMP_CODE_UNREACH_PORT         3
#define ICMP_CODE_UNREACH_NEEDFRAG     4
#define ICMP_CODE_UNREACH_SRCFAIL      5
#define ICMP_CODE_UNREACH_NET_UNKNOWN  6
#define ICMP_CODE_UNREACH_HOST_UNKNOWN 7
#define ICMP_CODE_UNREACH_ISOLATED     8
#define ICMP_CODE_UNREACH_NET_PROHIB   9
#define ICMP_CODE_UNREACH_HOST_PROHIB  10
#define ICMP_CODE_UNREACH_TOSNET       11
#define ICMP_CODE_UNREACH_TOSHOST      12

/**
  Get the IP header length from the struct EFI_IP4_HEADER. HeaderLength is
  Internet header length in 32-bit words, so HeaderLength<<2 is the real
  length of IP header.
  
  @param[out] HdrPtr   A pointer to EFI_IP4_HEADER
  
  @return The IP header length
**/
#define EFI_IP4_HEADER_LEN(HdrPtr) ((HdrPtr)->HeaderLength << 2)

/**
  To types of ICMP error which consist of ICMP header, IP header and original 
  datagram's data, get length from sum of ICMP header length, IP header length 
  and first 64 bits of datagram's data length.
  
  @param[in] IpHdr   A pointer to EFI_IP4_HEADER
  
  @return The ICMP error length
**/
#define ICMP_ERRLEN(IpHdr) \
  (sizeof(IP4_ICMP_HEAD) + EFI_IP4_HEADER_LEN(IpHdr) + 8)

/**
  Get the packet header from NET_BUF.
  
  @param[out]  Buf    A pointer to NET_BUF
  @param[in]   Type   Header type
  
  @return The pointer to packet header
**/
#define NET_PROTO_HDR(Buf, Type)  ((Type *) ((Buf)->BlockOp[0].Head))

  
extern EFI_IP4_CONFIG_DATA  mIp4IoDefaultIpConfigData;
extern EFI_IP6_CONFIG_DATA  mIp6IoDefaultIpConfigData;

#define IP_VERSION_4 4
#define IP_VERSION_6 6

///
/// This error will be delivered to the
/// listening transportation layer protocol
/// that consumes IpIO.
///

#define  ICMP_ERR_UNREACH_NET           0
#define  ICMP_ERR_UNREACH_HOST          1
#define  ICMP_ERR_UNREACH_PROTOCOL      2
#define  ICMP_ERR_UNREACH_PORT          3
#define  ICMP_ERR_MSGSIZE               4
#define  ICMP_ERR_UNREACH_SRCFAIL       5
#define  ICMP_ERR_TIMXCEED_INTRANS      6
#define  ICMP_ERR_TIMXCEED_REASS        7
#define  ICMP_ERR_QUENCH                8
#define  ICMP_ERR_PARAMPROB             9

#define  ICMP6_ERR_UNREACH_NET          0
#define  ICMP6_ERR_UNREACH_HOST         1
#define  ICMP6_ERR_UNREACH_PROTOCOL     2
#define  ICMP6_ERR_UNREACH_PORT         3
#define  ICMP6_ERR_PACKAGE_TOOBIG       4
#define  ICMP6_ERR_TIMXCEED_HOPLIMIT    5
#define  ICMP6_ERR_TIMXCEED_REASS       6
#define  ICMP6_ERR_PARAMPROB_HEADER     7
#define  ICMP6_ERR_PARAMPROB_NEXHEADER  8
#define  ICMP6_ERR_PARAMPROB_IPV6OPTION 9

///
/// The helper struct for IpIoGetIcmpErrStatus(). It is for internal use only.
///
typedef struct {
  BOOLEAN                   IsHard;
  BOOLEAN                   Notify;
} ICMP_ERROR_INFO;

typedef union {
  EFI_IP4_COMPLETION_TOKEN  Ip4Token;
  EFI_IP6_COMPLETION_TOKEN  Ip6Token;
} IP_IO_IP_COMPLETION_TOKEN;

typedef union {
  EFI_IP4_TRANSMIT_DATA     Ip4TxData;
  EFI_IP6_TRANSMIT_DATA     Ip6TxData;
} IP_IO_IP_TX_DATA;

typedef union {
  EFI_IP4_RECEIVE_DATA      Ip4RxData;
  EFI_IP6_RECEIVE_DATA      Ip6RxData;
} IP_IO_IP_RX_DATA;

typedef union {
  EFI_IP4_OVERRIDE_DATA     Ip4OverrideData;
  EFI_IP6_OVERRIDE_DATA     Ip6OverrideData;
} IP_IO_OVERRIDE;

typedef union {
  EFI_IP4_CONFIG_DATA       Ip4CfgData;
  EFI_IP6_CONFIG_DATA       Ip6CfgData;
} IP_IO_IP_CONFIG_DATA;

typedef union {
  EFI_IP4_HEADER            *Ip4Hdr;
  EFI_IP6_HEADER            *Ip6Hdr;
} IP_IO_IP_HEADER;

typedef union {
  IP4_ADDR                  SubnetMask;
  UINT8                     PrefixLength;
} IP_IO_IP_MASK;

///
/// The IP session for an IP receive packet.
///
typedef struct _EFI_NET_SESSION_DATA {
  EFI_IP_ADDRESS        Source;     ///< Source IP of the received packet
  EFI_IP_ADDRESS        Dest;       ///< Destination IP of the received packet
  IP_IO_IP_HEADER       IpHdr;      ///< IP header of the received packet
  UINT8                 IpVersion;  ///< The IP version of the received packet
} EFI_NET_SESSION_DATA;

/**
  The prototype is called back when an IP packet is received.
  
  @param[in] Status        Result of the receive request
  @param[in] IcmpErr       Valid when Status is EFI_ICMP_ERROR
  @param[in] NetSession    The IP session for the received packet
  @param[in] Pkt           Packet received
  @param[in] Context       The data provided by the user for the received packet when
                           the callback is registered in IP_IO_OPEN_DATA::RcvdContext.
  
**/
typedef
VOID
(*PKT_RCVD_NOTIFY) (
  IN EFI_STATUS           Status, 
  IN UINT8                IcmpErr,
  IN EFI_NET_SESSION_DATA *NetSession,
  IN NET_BUF              *Pkt,
  IN VOID                 *Context
  );

/**
  The prototype is called back when an IP packet is sent.
  
  @param[in] Status        Result of the sending
  @param[in] Context       The data provided by user for the received packet when
                           the callback is registered in IP_IO_OPEN_DATA::SndContext.
  @param[in] Sender        A pointer to EFI_IP4_PROTOCOL or EFI_IP6_PROTOCOL
  @param[in] NotifyData    Context data specified when calling IpIoSend()
  
**/
typedef
VOID
(*PKT_SENT_NOTIFY) (
  IN EFI_STATUS  Status,
  IN VOID        *Context,
  IN VOID        *Sender,
  IN VOID        *NotifyData
  );

///
/// This data structure wraps Ip4/Ip6 instances. The IpIo Library uses it for all
/// Ip4/Ip6 operations.
///
typedef struct _IP_IO {
  ///
  /// The node used to link this IpIo to the active IpIo list.
  ///
  LIST_ENTRY                    Entry;

  ///
  /// The list used to maintain the IP instance for different sending purpose.
  ///
  LIST_ENTRY                    IpList;
  
  EFI_HANDLE                    Controller;
  EFI_HANDLE                    Image;
  EFI_HANDLE                    ChildHandle;
  //
  // The IP instance consumed by this IP_IO
  //
  VOID                          *Ip;
  BOOLEAN                       IsConfigured;

  ///
  /// Some ip config data can be changed
  ///
  UINT8                         Protocol;

  ///
  /// Token and event used to get data from IP
  ///
  IP_IO_IP_COMPLETION_TOKEN     RcvToken; 

  ///
  /// List entry used to link the token passed to IP_IO
  ///
  LIST_ENTRY                    PendingSndList;

  //
  // User interface used to get notify from IP_IO
  //
  VOID                          *RcvdContext;    ///< See IP_IO_OPEN_DATA::RcvdContext
  VOID                          *SndContext;     ///< See IP_IO_OPEN_DATA::SndContext
  PKT_RCVD_NOTIFY               PktRcvdNotify;   ///< See IP_IO_OPEN_DATA::PktRcvdNotify
  PKT_SENT_NOTIFY               PktSentNotify;   ///< See IP_IO_OPEN_DATA::PktSentNotify
  UINT8                         IpVersion;
} IP_IO;

///
/// The struct is for the user to pass IP configuration and callbacks to IP_IO.
/// It is used by IpIoOpen().
///
typedef struct _IP_IO_OPEN_DATA {
  IP_IO_IP_CONFIG_DATA IpConfigData;    ///< Configuration of the IP instance
  VOID                 *RcvdContext;    ///< Context data used by receive callback
  VOID                 *SndContext;     ///< Context data used by send callback
  PKT_RCVD_NOTIFY      PktRcvdNotify;   ///< Receive callback
  PKT_SENT_NOTIFY      PktSentNotify;   ///< Send callback
} IP_IO_OPEN_DATA;

///
/// Internal struct book-keeping send request of IP_IO.
///
/// An IP_IO_SEND_ENTRY will be created each time a send request is issued to
/// IP_IO via IpIoSend().
///
typedef struct _IP_IO_SEND_ENTRY {
  LIST_ENTRY                Entry;
  IP_IO                     *IpIo;
  VOID                      *Context;
  VOID                      *NotifyData;
  VOID                      *Ip;
  NET_BUF                   *Pkt;
  IP_IO_IP_COMPLETION_TOKEN SndToken;
} IP_IO_SEND_ENTRY;

///
/// The IP_IO_IP_INFO is used in IpIoSend() to override the default IP instance
/// in IP_IO.
///
typedef struct _IP_IO_IP_INFO {
  EFI_IP_ADDRESS            Addr;
  IP_IO_IP_MASK             PreMask;
  LIST_ENTRY                Entry;
  EFI_HANDLE                ChildHandle;
  VOID                      *Ip;
  IP_IO_IP_COMPLETION_TOKEN DummyRcvToken;
  INTN                      RefCnt;
  UINT8                     IpVersion;
} IP_IO_IP_INFO;

/**
  Create a new IP_IO instance.
  
  This function uses IP4/IP6 service binding protocol in Controller to create
  an IP4/IP6 child (aka IP4/IP6 instance).

  @param[in]  Image             The image handle of the driver or application that
                                consumes IP_IO.
  @param[in]  Controller        The controller handle that has IP4 or IP6 service
                                binding protocol installed.
  @param[in]  IpVersion         The version of the IP protocol to use, either
                                IPv4 or IPv6.                            

  @return Pointer to a newly created IP_IO instance, or NULL if failed.

**/
IP_IO *
EFIAPI
IpIoCreate (
  IN EFI_HANDLE Image,
  IN EFI_HANDLE Controller,
  IN UINT8      IpVersion
  );

/**
  Destroy an IP_IO instance.
  
  This function is paired with IpIoCreate(). The IP_IO will be closed first.
  Resource will be freed afterwards. See IpIoClose().

  @param[in, out]  IpIo         Pointer to the IP_IO instance that needs to be
                                destroyed.

  @retval          EFI_SUCCESS  The IP_IO instance destroyed successfully.
  @retval          Others       Error condition occurred.

**/
EFI_STATUS
EFIAPI
IpIoDestroy (
  IN OUT IP_IO *IpIo
  );

/**
  Stop an IP_IO instance.
  
  This function is paired with IpIoOpen(). The IP_IO will be unconfigured, and all
  pending send/receive tokens will be canceled.

  @param[in, out]  IpIo            Pointer to the IP_IO instance that needs to stop.

  @retval          EFI_SUCCESS     The IP_IO instance stopped successfully.
  @retval          Others          Error condition occurred.

**/
EFI_STATUS
EFIAPI
IpIoStop (
  IN OUT IP_IO *IpIo
  );

/**
  Open an IP_IO instance for use.
  
  This function is called after IpIoCreate(). It is used for configuring the IP
  instance and register the callbacks and their context data for sending and
  receiving IP packets.

  @param[in, out]  IpIo               Pointer to an IP_IO instance that needs
                                      to open.
  @param[in]       OpenData           The configuration data and callbacks for
                                      the IP_IO instance.

  @retval          EFI_SUCCESS        The IP_IO instance opened with OpenData
                                      successfully.
  @retval          EFI_ACCESS_DENIED  The IP_IO instance is configured, avoid to 
                                      reopen it.
  @retval          Others             Error condition occurred.

**/
EFI_STATUS
EFIAPI
IpIoOpen (
  IN OUT IP_IO           *IpIo,
  IN     IP_IO_OPEN_DATA *OpenData
  );

/**
  Send out an IP packet.
  
  This function is called after IpIoOpen(). The data to be sent are wrapped in
  Pkt. The IP instance wrapped in IpIo is used for sending by default, but can be
  overriden by Sender. Other sending configurations, such as source address and gateway
  address, are specified in OverrideData.

  @param[in, out]  IpIo                  Pointer to an IP_IO instance used for sending IP
                                         packet.
  @param[in, out]  Pkt                   Pointer to the IP packet to be sent.
  @param[in]       Sender                Optional. The IP protocol instance used for sending.
  @param[in]       Context               Optional context data.
  @param[in]       NotifyData            Optional notify data.
  @param[in]       Dest                  The destination IP address to send this packet to.
  @param[in]       OverrideData          The data to override some configuration of the IP
                                         instance used for sending.

  @retval          EFI_SUCCESS           The operation is completed successfully.
  @retval          EFI_NOT_STARTED       The IpIo is not configured.
  @retval          EFI_OUT_OF_RESOURCES  Failed due to resource limit.

**/
EFI_STATUS
EFIAPI
IpIoSend (
  IN OUT IP_IO          *IpIo,
  IN OUT NET_BUF        *Pkt,
  IN     IP_IO_IP_INFO  *Sender        OPTIONAL,
  IN     VOID           *Context       OPTIONAL,
  IN     VOID           *NotifyData    OPTIONAL,
  IN     EFI_IP_ADDRESS *Dest,
  IN     IP_IO_OVERRIDE *OverrideData  OPTIONAL
  );

/**
  Cancel the IP transmit token which wraps this Packet.

  @param[in]  IpIo                  Pointer to the IP_IO instance.
  @param[in]  Packet                Pointer to the packet of NET_BUF to cancel.

**/
VOID
EFIAPI
IpIoCancelTxToken (
  IN IP_IO  *IpIo,
  IN VOID   *Packet
  );

/**
  Add a new IP instance for sending data.
  
  The function is used to add the IP_IO to the IP_IO sending list. The caller
  can later use IpIoFindSender() to get the IP_IO and call IpIoSend() to send
  data.

  @param[in, out]  IpIo               Pointer to an IP_IO instance to add a new IP
                                      instance for sending purposes.

  @return Pointer to the created IP_IO_IP_INFO structure, NULL if failed.

**/
IP_IO_IP_INFO *
EFIAPI
IpIoAddIp (
  IN OUT IP_IO  *IpIo
  );

/**
  Configure the IP instance of this IpInfo and start the receiving if IpConfigData
  is not NULL.

  @param[in, out]  IpInfo          Pointer to the IP_IO_IP_INFO instance.
  @param[in, out]  IpConfigData    The IP4 or IP6 configure data used to configure 
                                   the IP instance. If NULL, the IP instance is reset.
                                   If UseDefaultAddress is set to TRUE, and the configure
                                   operation succeeds, the default address information
                                   is written back in this IpConfigData.

  @retval          EFI_SUCCESS     The IP instance of this IpInfo is configured successfully,
                                   or there is no need to reconfigure it.
  @retval          Others          Configuration failed.

**/
EFI_STATUS
EFIAPI
IpIoConfigIp (
  IN OUT IP_IO_IP_INFO        *IpInfo,
  IN OUT VOID                 *IpConfigData OPTIONAL
  );

/**
  Destroy an IP instance maintained in IpIo->IpList for
  sending purpose.
  
  This function pairs with IpIoAddIp(). The IpInfo is previously created by
  IpIoAddIp(). The IP_IO_IP_INFO::RefCnt is decremented and the IP instance
  will be dstroyed if the RefCnt is zero.

  @param[in]  IpIo                  Pointer to the IP_IO instance.
  @param[in]  IpInfo                Pointer to the IpInfo to be removed.

**/
VOID
EFIAPI
IpIoRemoveIp (
  IN IP_IO            *IpIo,
  IN IP_IO_IP_INFO    *IpInfo
  );

/**
  Find the first IP protocol maintained in IpIo whose local
  address is the same as Src.
  
  This function is called when the caller needs the IpIo to send data to the
  specified Src. The IpIo was added previously by IpIoAddIp().

  @param[in, out]  IpIo              Pointer to the pointer of the IP_IO instance.
  @param[in]       IpVersion         The version of the IP protocol to use, either
                                     IPv4 or IPv6.
  @param[in]       Src               The local IP address.

  @return Pointer to the IP protocol can be used for sending purpose and its local
          address is the same with Src.

**/
IP_IO_IP_INFO *
EFIAPI
IpIoFindSender (
  IN OUT IP_IO           **IpIo,
  IN     UINT8           IpVersion,
  IN     EFI_IP_ADDRESS  *Src
  );

/**
  Get the ICMP error map information.
  
  The ErrorStatus will be returned. The IsHard and Notify are optional. If they
  are not NULL, this routine will fill them.

  @param[in]   IcmpError             IcmpError Type.
  @param[in]   IpVersion             The version of the IP protocol to use,
                                     either IPv4 or IPv6.
  
  @param[out]  IsHard                Whether it is a hard error.
  @param[out]  Notify                Whether it need to notify SockError.

  @return ICMP Error Status, such as EFI_NETWORK_UNREACHABLE.

**/
EFI_STATUS
EFIAPI
IpIoGetIcmpErrStatus (
  IN  UINT8       IcmpError,
  IN  UINT8       IpVersion,
  OUT BOOLEAN     *IsHard  OPTIONAL,
  OUT BOOLEAN     *Notify  OPTIONAL
  );

/**
  Refresh the remote peer's Neighbor Cache entries.

  This function is called when the caller needs the IpIo to refresh the existing
  IPv6 neighbor cache entries since the neighbor is considered reachable by the 
  node has recently received a confirmation that packets sent recently to the 
  neighbor were received by its IP layer. 

  @param[in]   IpIo                  Pointer to an IP_IO instance
  @param[in]   Neighbor              The IP address of the neighbor
  @param[in]   Timeout               Time in 100-ns units that this entry will
                                     remain in the neighbor cache. A value of 
                                     zero means that the entry is permanent. 
                                     A value of non-zero means that the entry is 
                                     dynamic and will be deleted after Timeout.

  @retval      EFI_SUCCESS           The operation is completed successfully.
  @retval      EFI_NOT_STARTED       The IpIo is not configured.
  @retval      EFI_INVALID_PARAMETER Neighbor Address is invalid.
  @retval      EFI_NOT_FOUND         The neighbor cache entry is not in the 
                                     neighbor table.  
  @retval      EFI_OUT_OF_RESOURCES  Failed due to resource limit.

**/
EFI_STATUS
IpIoRefreshNeighbor (
  IN IP_IO           *IpIo,
  IN EFI_IP_ADDRESS  *Neighbor,
  IN UINT32          Timeout  
  );

#endif

