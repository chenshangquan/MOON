
/* api_errno_fmt.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2005-11-30 zhuzhenming write first.
 */

#ifndef _API_ERRNO_FMT_H_
#define _API_ERRNO_FMT_H_

/* zhuzhm : general */
#define NIP_API_ARGV_ERROR_FMT                          "%% Invalid parameter %s"
#define NIP_API_ARGV_ERROR_FMT_C                      "%% ��Ч�Ĳ��� %s"
#define NIP_API_COMM_ERROR_FMT                          "%% Nip api communication error %s"
#define NIP_API_IF_NOT_EXIST_FMT                        "%% Interface not exist %s"
#define NIP_API_IF_NOT_EXIST_FMT_C                    "%% �ӿڲ����� %s"
#define NIP_API_ADDR_NOT_EXIST_FMT                  "%% Address not eixst %s"
#define NIP_API_ADDR_NOT_EXIST_FMT_C               "%% ��ַ������%s"

/* zhuzhm : interface */
#define IF_E_MALFORMED_ADDR_FMT     "%% Malformed address %s"
#define IF_E_MALFORMED_ADDR_FMT_C     "%%��Ч�ĵ�ַ��ʽ%s"
#define IF_E_HIGHEST_ADDR_ERROR_FMT     "%% Highest byte shouldn't be 0 or 127 %s"
#define IF_E_HIGHEST_ADDR_ERROR_FMT_C   "%%��ַ������0��127��ͷ%s"
#define IF_E_PREFIX_IS_ZERO_FMT     "%% Prefix shouldn't be 0 %s"
#define IF_E_PREFIX_IS_ZERO_FMT_C   "%%���볤�Ȳ�����0%s"
#define IF_E_ADDR_IS_MULTI_FMT     "%% Highest byte should be smaller than 224 %s"
#define IF_E_ADDR_IS_MULTI_FMT_C    "%%��ַ��ͷ���ܱ�224��%s"
#define IF_E_CONFLIT_WITH_LOOPBACK_FMT     "%% Prefix shouldn't conflict with loopback address %s"
#define IF_E_CONFLIT_WITH_LOOPBACK_FMT_C    "%%�ͻ��ؽӿڵ�ַ��ͻ%s"
#define IF_E_PREFIX_LEN_INVALID_FMT     "%% Prefix length shouldn't be 32 %s"
#define IF_E_PREFIX_LEN_INVALID_FMT_C   "%%���볤�Ȳ�����32%s"
#define IF_E_PREFIX_INVALID_FMT     "%% Prefix shouldn't be network address or broadcast address %s"
#define IF_E_PREFIX_INVALID_FMT_C   "%%�����������ַ�͹㲥��ַ%s"
#define IF_E_CONFLIT_WITH_OTHER_ADDR_FMT     "%% Conflict with other interface's addresses %s"
#define IF_E_CONFLIT_WITH_OTHER_ADDR_FMT_C  "%%�������ӿ��ϵĵ�ַ��ͻ%s"
#define IF_E_CONFLIT_WITH_ADDR_FMT     "%% Conflict with the interface's addresses %s"
#define IF_E_CONFLIT_WITH_ADDR_FMT_C    "%%�ͱ��ӿ��ϵĵ�ַ��ͻ%s"
#define IF_E_NO_MASTER_ADDR_FMT   "%% Must add primary before adding secondary %s"
#define IF_E_NO_MASTER_ADDR_FMT_C   "%%�����õڶ���ַǰ��������������ַ%s"
#define IF_E_SET_ADDR_FAILED_FMT   "%% Can't set interface IP address: %s.%s"
#define IF_E_SET_ADDR_FAILED_FMT_C  "%%���õ�ַʧ��:%s.%s"

#define IF_E_ADDR_NOT_FOUND_FMT   "%% Can't find address%s"
#define IF_E_ADDR_NOT_FOUND_FMT_C   "%%�Ҳ�����ַ%s"
#define IF_E_DELETE_SECOND_ADDR_FIRST_FMT   "%% Must delete secondary before deleting primary%s"
#define IF_E_DELETE_SECOND_ADDR_FIRST_FMT_C "%%ɾ������ַǰ������ɾ���ڶ���ַ%s"
#define IF_E_UNSET_ADDR_FAILED_FMT   "%% Can't unset interface IP address: %s.%s"
#define IF_E_UNSET_ADDR_FAILED_FMT_C "%%ɾ����ַʧ��%s%s"
#define IF_E_NOT_CONF_ADDR_FMT   "%% This is not configured address %s"
#define IF_E_NOT_CONF_ADDR_FMT_C    "%%�ⲻ�����õĵ�ַ%s"
#define IF_E_SECOND_IP_ADDR_REACH_MAX_FMT  "%% Secondary ip addresses have reached max.%s"
#define IF_E_SECOND_IP_ADDR_REACH_MAX_FMT_C "%%�ڶ���ַ��������Ŀ�ﵽ���%s"

#define IF_E_ADDR_IS_NOT_GROUP_FMT          "%% Not a IP multicast group address%s"
#define IF_E_ADDR_IS_NOT_GROUP_FMT_C      "%% �����鲥��ַ%s"
#define IF_E_GROUP_IS_WELLKNOW_FMT          "%% Illegal multicast group address%s"
#define IF_E_GROUP_IS_WELLKNOW_FMT_C         "%%���ܼ���֪����%s"
#define IF_E_GROUP_NOT_FOUND_FMT                "%%Group not found%s"
#define IF_E_GROUP_NOT_FOUND_FMT_C              "%%���ַ������%s"
#define IF_E_CFG_GROUP_REACH_MAX_FMT        "%%Configed group address reach max%s"
#define IF_E_CFG_GROUP_REACH_MAX_FMT_C      "%%�����õ��鲥��ַ��Ŀ�ﵽ���%s"
#define IF_E_JOIN_GROUP_FAILED_FMT              "%%Join group failed%s"
#define IF_E_JOIN_GROUP_FAILED_FMT_C          "%%������ʧ��%s"
#define IF_E_LEAVE_GROUP_FAILED_FMT             "%%Leave group failed%s"
#define IF_E_LEAVE_GROUP_FAILED_FMT_C           "%%�뿪��ʧ��%s"

#define IF_SHUTDOWN_ERROR_FMT                   "%% Can't shutdown interface%s"
#define IF_SHUTDOWN_ERROR_FMT_C     "%%�رսӿ�ʧ��%s"
#define IF_SHUTDOWN_NOT_SUPPORT_FMT      "%% Shutdown not allowed on the interface.%s"
#define IF_SHUTDOWN_NOT_SUPPORT_FMT_C   "%%�˽ӿڲ�����ر�%s"

/* interface status */
#define IF_E_NOT_UP_FMT                     "%%Interface not up%s"
#define IF_E_NOT_UP_FMT_C                   "%%�ӿ�û��UP%s"
#define IF_E_NOT_MULTICAST_FMT          "%%Interface not multicast%s"
#define IF_E_NOT_MULTICAST_FMT_C        "%%�ӿڲ�֧�ֶಥ%s"

/* zhuzhm : route */
#define RT_E_MALFORMED_PREFIX_FMT         "%% Malformed prefix address%s"
#define RT_E_MALFORMED_PREFIX_FMT_C "%%��Ч�ĵ�ַ��ʽ%s"
#define RT_E_INVALID_PREFIX_FMT         "%% Invalid prefix address %s"
#define RT_E_INVALID_PREFIX_FMT_C       "%%��Ч�ĵ�ַ%s"
#define RT_E_MALFORMED_MASK_FMT         "%% Malformed mask address%s"
#define RT_E_MALFORMED_MASK_FMT_C       "%%��Ч�������ʽ%s"
#define RT_E_INVALID_MASK_FMT         "%% Invalid mask address%s"
#define RT_E_INVALID_MASK_FMT_C     "%%��Ч������%s"
#define RT_E_INVALID_GATE_FMT         "%% Invalid nexthop address%s"
#define RT_E_INVALID_GATE_FMT_C     "%%��Ч����һ����ַ%s"
#define RT_E_NO_MATCH_ROUTE_FMT		"%%No matching route to delete%s"
#define RT_E_NO_MATCH_ROUTE_FMT_C	"%%û���ҵ�������%s"
#define RT_E_INVALID_DISTANCE_FMT		"%%Invalid distance%s"
#define RT_E_INVALID_DISTANCE_FMT_C	"%%��Ч�ľ���%s"


/* zhuzhm : ethernet */
#define ETH_E_INVALID_MAC_ADDR_FMT          "%% Invalidation mac address%s"
#define ETH_E_INVALID_MAC_ADDR_FMT_C        "%%��Ч��MAC��ַ%s"
#define ETH_E_SET_MAC_ADDR_FAILED_FMT    "%% Can't set mac address%s"
#define ETH_E_SET_MAC_ADDR_FAILED_FMT_C "%%����MAC��ַʧ��%s"
#define ETH_E_NO_CONFIG_FMT                                 "%% There is no configure%s"
#define ETH_E_NO_CONFIG_FMT_C                   "%%û������%s"
#define ETH_E_CONFIG_NOT_EXIST_FMT                   "%% Configure not exist%s"
#define ETH_E_CONFIG_NOT_EXIST_FMT_C            "%%�����Ѿ�����%s"
#define ETH_E_DEL_MAC_ADDR_FAILED_FMT                     "%% Can't delete mac address%s"
#define ETH_E_DEL_MAC_ADDR_FAILED_FMT_C     "%%ɾ��MAC��ַʧ��%s"

#endif  /* _API_ERRNO_FMT_H_ */

