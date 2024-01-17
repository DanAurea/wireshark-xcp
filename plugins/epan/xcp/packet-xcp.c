#include "config.h"
#include <epan/packet.h>

#define XCP_PORT_RANGE "5555,5556"

/* Standard commmand */
#define CMD_CONNECT 0xFF
#define CMD_DISCONNECT 0xFE
#define CMD_GET_STATUS 0xFD
#define CMD_SYNCH 0xFC
#define CMD_GET_COMM_MODE_INFO 0xFB
#define CMD_GET_ID 0xFA
#define CMD_SET_REQUEST 0xF9
#define CMD_GET_SEED 0xF8
#define CMD_UNLOCK 0xF7
#define CMD_SET_MTA 0xF6
#define CMD_UPLOAD 0xF5
#define CMD_SHORT_UPLOAD 0xF4
#define CMD_BUILD_CHECKSUM 0xF3
#define CMD_TRANSPORT_LAYER_CMD 0xF2
#define CMD_USER_CMD 0xF1

/* Calibration commmand */
#define CMD_DOWNLOAD 0xF0
#define CMD_DOWNLOAD_NEXT 0xEF
#define CMD_DOWNLOAD_MAX 0xEE
#define CMD_SHORT_DOWNLOAD 0xED
#define CMD_MODIFY_BITS 0xEC

/* Page change commmand */
#define CMD_SET_CAL_PAGE 0xEB
#define CMD_GET_CAL_PAGE 0xEA
#define CMD_GET_PAG_PROCESSOR_INFO 0xE9
#define CMD_GET_SEGMENT_INFO 0xE8
#define CMD_GET_PAGE_INFO 0xE7
#define CMD_SET_SEGMENT_MODE 0xE6
#define CMD_GET_SEGMENT_MODE 0xE5
#define CMD_COPY_CAL_PAGE 0xE4

/* Periodic data exchange */
#define CMD_SET_DAQ_PTR 0xE2
#define CMD_WRITE_DAQ 0xE1
#define CMD_SET_DAQ_LIST_MODE 0xE0
#define CMD_GET_DAQ_LIST_MODE 0xDF
#define CMD_START_STOP_DAQ_LIST 0xDE
#define CMD_START_STOP_SYNCH 0xDD
#define CMD_WRITE_DAQ_MULTIPLE 0xC7
#define CMD_READ_DAQ 0xDB
#define CMD_GET_DAQ_CLOCK 0xDC
#define CMD_GET_DAQ_PROCESSOR_INFO 0xDA
#define CMD_GET_DAQ_RESOLUTION_INFO 0xD9
#define CMD_GET_DAQ_LIST_INFO 0xD8
#define CMD_GET_DAQ_EVENT_INFO 0xD7

/* Periodic data exchange static configuration */
#define CMD_CLEAR_DAQ_LIST 0xE3

/* Cyclic data exchange dynamic configuration */
#define CMD_FREE_DAQ 0xD6
#define CMD_ALLOC_DAQ 0xD5
#define CMD_ALLOC_ODT 0xD4
#define CMD_ALLOC_ODT_ENTRY 0xD3

/* Flash programming */
#define CMD_PROGRAM_START 0xD2
#define CMD_PROGRAM_CLEAR 0xD1
#define CMD_PROGRAM 0xD0
#define CMD_PROGRAM_RESET 0xCF
#define CMD_GET_PGM_PROCESSOR_INFO 0xCE
#define CMD_GET_SECTOR_INFO 0xCD
#define CMD_PROGRAM_PREPARE 0xCC
#define CMD_PROGRAM_FORMAT 0xCB
#define CMD_PROGRAM_NEXT 0xCA
#define CMD_PROGRAM_MAX 0xC9
#define CMD_PROGRAM_VERIFY 0xC8

/* Response */
#define CMD_POSITIVE_RESPONSE 0xFF
#define CMD_NEGATIVE_RESPONSE 0xFE
#define CMD_EVENT_PACKET 0xFD
#define CMD_SERVICE_PACKET 0xFC

/* Command response */
#define CMD_CONNECT_POSITIVE_RESPONSE 0xFF
#define CMD_STATUS_POSITIVE_RESPONSE 0xFD
#define CMD_COMMON_MODE_INFO_POSITIVE_RESPONSE 0xFB
#define CMD_ID_POSITIVE_RESPONSE 0xFA
#define CMD_SEED_POSITIVE_RESPONSE 0xF8
#define CMD_UNLOCK_POSITIVE_RESPONSE 0xF7
#define CMD_UPLOAD_POSITIVE_RESPONSE 0xF5
#define CMD_SHORT_UPLOAD_POSITIVE_RESPONSE 0xF4
#define CMD_CHECKSUM_POSITIVE_RESPONSE 0xF3
#define CMD_CAL_PAGE_POSITIVE_RESPONSE 0xEA
#define CMD_PAG_PROCESSOR_INFO_POSITIVE_RESPONSE 0xE9
#define CMD_PAGE_INFO_POSITIVE_RESPONSE 0xE7
#define CMD_SEGMENT_MODE_INFO_POSITIVE_RESPONSE 0xE5
#define CMD_DAQ_LIST_POSITIVE_RESPONSE 0xDF
#define CMD_START_STOP_DAQ_LIST_POSITIVE_RESPONSE 0xDE
#define CMD_DAQ_CLOCK_LIST_POSITIVE_RESPONSE 0xDC
#define CMD_READ_DAQ_POSITIVE_RESPONSE 0xDB
#define CMD_DAQ_PROCESSOR_INFO_POSITIVE_RESPONSE 0xDA
#define CMD_DAQ_RESOLUTION_INFO_POSITIVE_RESPONSE 0xD9
#define CMD_DAQ_LIST_INFO_POSITIVE_RESPONSE 0xD8
#define CMD_DAQ_EVENT_INFO_POSITIVE_RESPONSE 0xD7
#define CMD_PROGRAM_START_POSITIVE_RESPONSE 0xD2
#define CMD_PGM_PROCESSOR_POSITIVE_RESPONSE 0xCE
#define CMD_SECTOR_INFO_POSITIVE_RESPONSE 0xCD

/* Connection mode */
#define CMD_CONNECT_NORMAL_MODE 0x00
#define CMD_CONNECT_USER_MODE 0x01

/* Get identifier types */
#define CMD_GET_ID_ASCII 0x00
#define CMD_GET_ID_FILENAME_WITHOUT_PATH_AND_EXTENSION 0x01
#define CMD_GET_ID_FILENAME_WITH_PATH_AND_EXTENSION 0x02
#define CMD_GET_ID_URL 0x03
#define CMD_GET_ID_FILE 0x04

/* Set request mode */
#define CMD_SET_REQUEST_STORE_CAL_REQ 0x01 << 0
#define CMD_SET_REQUEST_STORE_DAQ_REQ 0x01 << 1
#define CMD_SET_REQUEST_CLEAR_DAQ_REQ 0x01 << 2
#define CMD_SET_REQUEST_X3 0x01 << 3
#define CMD_SET_REQUEST_X4 0x01 << 4
#define CMD_SET_REQUEST_X5 0x01 << 5
#define CMD_SET_REQUEST_X6 0x01 << 6
#define CMD_SET_REQUEST_X7 0x01 << 7

/* Get seed mode */
#define CMD_GET_SEED_MODE_FIRST 0x00
#define CMD_GET_SEED_MODE_REMAINING 0x01

/* Get seed resource */
#define CMD_GET_SEED_RESOURCE 0x00
#define CMD_GET_SEED_IGNORE 0x01

/* Transport layer sub command */
#define CMD_TRANSPORT_LAYER_GET_SLAVE_ID 0xFF
#define CMD_TRANSPORT_LAYER_GET_DAQ_ID 0xFE
#define CMD_TRANSPORT_LAYER_SET_DAQ_ID 0xFD

/* Transport layer get id echo mode */
#define CMD_TRANSPORT_LAYER_GET_ID_IDENTIFY_BY_ECHO 0x00
#define CMD_TRANSPORT_LAYER_GET_ID_CONFIRM_BY_INVERSE_ECHO 0x01

/* Set cal page mode */
#define CMD_SET_CAL_PAGE_ECU  0x01 << 0
#define CMD_SET_CAL_PAGE_XCP 0x01 << 1
#define CMD_SET_CAL_PAGE_X2 0x01 << 2
#define CMD_SET_CAL_PAGE_X3 0x01 << 3
#define CMD_SET_CAL_PAGE_X4 0x01 << 4
#define CMD_SET_CAL_PAGE_X5 0x01 << 5
#define CMD_SET_CAL_PAGE_X6 0x01 << 6
#define CMD_SET_CAL_PAGE_ALL 0x01 << 7

/* Get segment info mode */
#define CMD_GET_SEGMENT_INFO_MODE_GET_BASIC_ADDRESS_INFO 0x00
#define CMD_GET_SEGMENT_INFO_MODE_GET_STANDARD_INFO 0x01
#define CMD_GET_SEGMENT_INFO_MODE_GET_ADDRESS_MAPPING_INFO 0x02

/* Set segment mode */
#define CMD_SET_SEGMENT_MODE_FREEZE 0x01 << 0
#define CMD_SET_SEGMENT_MODE_X1 0x01 << 1
#define CMD_SET_SEGMENT_MODE_X2 0x01 << 2
#define CMD_SET_SEGMENT_MODE_X3 0x01 << 3
#define CMD_SET_SEGMENT_MODE_X4 0x01 << 4
#define CMD_SET_SEGMENT_MODE_X5 0x01 << 5
#define CMD_SET_SEGMENT_MODE_X6 0x01 << 6
#define CMD_SET_SEGMENT_MODE_X7 0x01 << 7

/* Set DAQ list mode */
#define CMD_SET_DAQ_LIST_MODE_X0 0x01 << 0
#define CMD_SET_DAQ_LIST_MODE_DIRECTION 0x01 << 1
#define CMD_SET_DAQ_LIST_MODE_X2 0x01 << 2
#define CMD_SET_DAQ_LIST_MODE_X3 0x01 << 3
#define CMD_SET_DAQ_LIST_MODE_TIMESTAMP 0x01 << 4
#define CMD_SET_DAQ_LIST_MODE_PID_OFF 0x01 << 5
#define CMD_SET_DAQ_LIST_MODE_X6 0x01 << 6
#define CMD_SET_DAQ_LIST_MODE_X7 0x01 << 7

/* Start stop DAQ list mode */
#define CMD_START_STOP_DAQ_LIST_MODE_STOP 0x00
#define CMD_START_STOP_DAQ_LIST_MODE_START 0x01
#define CMD_START_STOP_DAQ_LIST_MODE_SELECT 0x02

/* Start stop synch mode */
#define CMD_START_STOP_SYNCH_MODE_STOP 0x00
#define CMD_START_STOP_SYNCH_MODE_START 0x01
#define CMD_START_STOP_SYNCH_MODE_SELECT 0x02

/* Program clear mode*/
#define CMD_PROGRAM_CLEAR_ABSOLUTE_ACCESS 0x00
#define CMD_PROGRAM_CLEAR_FUNCTIONAL_ACCESS 0x01

/* Get sector info address mode */
#define CMD_GET_SECTOR_INFO_ADDRESS_MODE_GET_ADDRESS 0X00
#define CMD_GET_SECTOR_INFO_ADDRESS_MODE_GET_LENGTH 0X01

/* Program verify start mode */
#define CMD_PROGRAM_VERIFY_START_MODE_REQUEST_TO_START_INTERNAL_ROUTINE 0X00
#define CMD_PROGRAM_VERIFY_START_MODE_SENDING_VERIFICATION_VALUE 0X01

static const value_string xcp_cmd[] = {
    /* Standard commmand */
    { CMD_CONNECT,              "Connect"},
    { CMD_DISCONNECT,           "Disconnect" },
    { CMD_GET_STATUS,           "Get status" },
    { CMD_SYNCH,                "Get synchronization" },
    { CMD_GET_COMM_MODE_INFO,   "Get command mode information" },
    { CMD_GET_ID,               "Get identifier" },
    { CMD_SET_REQUEST,          "Set request" },
    { CMD_GET_SEED,             "Get seed" },
    { CMD_UNLOCK,               "Unlock" },
    { CMD_SET_MTA,              "Set MTA" },
    { CMD_UPLOAD,               "Upload" },
    { CMD_SHORT_UPLOAD,         "Short upload" },
    { CMD_BUILD_CHECKSUM,       "Build checksum" },
    { CMD_TRANSPORT_LAYER_CMD,  "Transport layer command" },
    { CMD_USER_CMD,             "User command" },

    /* Calibration command */
    { CMD_DOWNLOAD,             "Download" },
    { CMD_DOWNLOAD_NEXT,        "Download next" },
    { CMD_DOWNLOAD_MAX,         "Download max" },
    { CMD_SHORT_DOWNLOAD,       "Short download" },
    { CMD_MODIFY_BITS,          "Modify bits" },

    /* Page change commmand */
    { CMD_SET_CAL_PAGE,             "Set calibration page"},
    { CMD_GET_CAL_PAGE,             "Get calibration page" },
    { CMD_GET_PAG_PROCESSOR_INFO,   "Get page processor information" },
    { CMD_GET_SEGMENT_INFO,         "Get segment information" },
    { CMD_GET_PAGE_INFO,            "Get page information" },
    { CMD_SET_SEGMENT_MODE,         "Set segment mode" },
    { CMD_GET_SEGMENT_MODE,         "Get segment mode" },
    { CMD_COPY_CAL_PAGE,            "Copy calibration page" },

    /* Periodic data exchange */
    { CMD_SET_DAQ_PTR,              "Set DAQ pointer"},
    { CMD_WRITE_DAQ,                "Write DAQ" },
    { CMD_SET_DAQ_LIST_MODE,        "Set DAQ list mode" },
    { CMD_GET_DAQ_LIST_MODE,        "Get DAQ list mode" },
    { CMD_START_STOP_DAQ_LIST,      "Start stop DAQ list" },
    { CMD_START_STOP_SYNCH,         "Start stop synchronization" },
    { CMD_WRITE_DAQ_MULTIPLE,       "Write DAQ multiple" },
    { CMD_READ_DAQ,                 "Read DAQ" },
    { CMD_GET_DAQ_CLOCK,            "Get DAQ clock" },
    { CMD_GET_DAQ_PROCESSOR_INFO,   "Get DAQ processor information" },
    { CMD_GET_DAQ_RESOLUTION_INFO,  "Get DAQ resolution information" },
    { CMD_GET_DAQ_LIST_INFO,        "Get DAQ list information" },
    { CMD_GET_DAQ_EVENT_INFO,       "Get DAQ event information" },

    /* Periodic data exchange static configuration */
    { CMD_CLEAR_DAQ_LIST,           "Clear DAQ list" },

    /* Cylic data exchange dynamic configuration */
    { CMD_FREE_DAQ,                 "Free DAQ"},
    { CMD_ALLOC_DAQ,                "Allocate DAQ" },
    { CMD_ALLOC_ODT,                "Allocate ODT" },
    { CMD_ALLOC_ODT_ENTRY,          "Allocate ODT entry" },

    /* Flash programming */
    { CMD_PROGRAM_START,            "Start program"},
    { CMD_PROGRAM_CLEAR,            "Clear program" },
    { CMD_PROGRAM,                  "Program" },
    { CMD_PROGRAM_RESET,            "Reset program" },
    { CMD_GET_PGM_PROCESSOR_INFO,   "Get program processor information" },
    { CMD_GET_SECTOR_INFO,          "Get sector information" },
    { CMD_PROGRAM_PREPARE,          "Prepare program" },
    { CMD_PROGRAM_FORMAT,           "Format program" },
    { CMD_PROGRAM_NEXT,             "Next program" },
    { CMD_PROGRAM_MAX,              "Max program" },
    { CMD_PROGRAM_VERIFY,           "Verify program" },

    { 0,             NULL }
};

static const value_string xcp_connection_mode[] = {
    /* Standard commmand */
    { CMD_CONNECT_NORMAL_MODE, "Normal"},
    { CMD_CONNECT_USER_MODE,   "User" },

    { 0,             NULL }
};

static const value_string xcp_get_id_type[] = {
    /* Standard commmand */
    { CMD_GET_ID_ASCII, "ASCII"},
    { CMD_GET_ID_FILENAME_WITHOUT_PATH_AND_EXTENSION, "Filename without path and extension"},
    { CMD_GET_ID_FILENAME_WITH_PATH_AND_EXTENSION, "Filename with path and extension"},
    { CMD_GET_ID_URL, "URL"},
    { CMD_GET_ID_FILE, "File"},

    { 0,             NULL }
};

static const value_string xcp_get_seed_mode[] = {
    /* Standard commmand */
    { CMD_GET_SEED_MODE_FIRST, "First"},
    { CMD_GET_SEED_MODE_REMAINING, "Remaining"},

    { 0,             NULL }
};

static const value_string xcp_get_seed_resource[] = {
    /* Standard commmand */
    { CMD_GET_SEED_RESOURCE, "Resource"},
    { CMD_GET_SEED_IGNORE, "Ignore"},

    { 0,             NULL }
};

static const value_string xcp_transport_layer_cmd[] = {
    /* Standard commmand */
    { CMD_TRANSPORT_LAYER_GET_SLAVE_ID, "Get slave ID"},
    { CMD_TRANSPORT_LAYER_GET_DAQ_ID, "Get DAQ ID"},
    { CMD_TRANSPORT_LAYER_SET_DAQ_ID, "Set DAQ ID"},

    { 0,             NULL }
};

static const value_string xcp_get_segment_info_mode[] = {
    /* Standard commmand */
    { CMD_GET_SEGMENT_INFO_MODE_GET_BASIC_ADDRESS_INFO, "Get basic address info"},
    { CMD_GET_SEGMENT_INFO_MODE_GET_STANDARD_INFO, "Get standard info"},
    { CMD_GET_SEGMENT_INFO_MODE_GET_ADDRESS_MAPPING_INFO, "Get address mapping info"},

    { 0,             NULL }
};

static const value_string xcp_start_stop_daq_list_mode[] = {
    /* Standard commmand */
    { CMD_START_STOP_DAQ_LIST_MODE_STOP, "Stop"},
    { CMD_START_STOP_DAQ_LIST_MODE_START, "Start"},
    { CMD_START_STOP_DAQ_LIST_MODE_SELECT, "Select"},

    { 0,             NULL }
};

static const value_string xcp_program_clear_mode[] = {
    /* Standard commmand */
    { CMD_PROGRAM_CLEAR_ABSOLUTE_ACCESS, "Absolute access"},
    { CMD_PROGRAM_CLEAR_FUNCTIONAL_ACCESS, "Functional access"},

    { 0,             NULL }
};

static const value_string xcp_get_sector_info_mode[] = {
    /* Standard commmand */
    { CMD_GET_SECTOR_INFO_ADDRESS_MODE_GET_ADDRESS, "Get address"},
    { CMD_GET_SECTOR_INFO_ADDRESS_MODE_GET_LENGTH, "Get length"},

    { 0,             NULL }
};

static const value_string xcp_program_verify_verification_mode[] = {
    /* Standard commmand */
    { CMD_PROGRAM_VERIFY_START_MODE_REQUEST_TO_START_INTERNAL_ROUTINE, "Request to start internal routine"},
    { CMD_PROGRAM_VERIFY_START_MODE_SENDING_VERIFICATION_VALUE, "Sending verification value"},

    { 0,             NULL }
};


static const enum_val_t address_granularity[] = {
    {"1", "1", 1},
    {"2", "2", 2},
    {"4", "4", 4},
    {NULL, NULL, -1}
};

static int proto_xcp;

static int hf_xcp_len;
static int hf_xcp_ctr;
static int hf_xcp_pid;
static int hf_xcp_fill;

static int hf_xcp_connection_mode;
static int hf_xcp_identification_type;

static int hf_xcp_set_request_mode_flags;
static int hf_xcp_set_request_store_cal_req_flag;
static int hf_xcp_set_request_store_daq_req_flag;
static int hf_xcp_set_request_clear_daq_req_flag;
static int hf_xcp_set_request_x3;
static int hf_xcp_set_request_x4;
static int hf_xcp_set_request_x5;
static int hf_xcp_set_request_x6;
static int hf_xcp_set_request_x7;

static int hf_xcp_set_request_session_configuration_id;

static int hf_xcp_get_seed_mode;
static int hf_xcp_get_seed_resource;

static int hf_xcp_unlock_seed_len;
static int hf_xcp_unlock_seed;

static int hf_xcp_set_mta_reserved;
static int hf_xcp_set_mta_address_extension;
static int hf_xcp_set_mta_address;

static int hf_xcp_upload_number_data_element;

static int hf_xcp_short_upload_number_data_element;
static int hf_xcp_short_upload_reserved;
static int hf_xcp_short_upload_address_extension;
static int hf_xcp_short_upload_address;

static int hf_xcp_build_checksum_reserved;
static int hf_xcp_build_checksum_block_size;

static int hf_xcp_transport_layer_cmd_subcommand;

static int hf_xcp_user_cmd_subcommand;

static int hf_xcp_download_number_data_elements;
static int hf_xcp_download_alignment;
static int hf_xcp_download_data_elements;

static int hf_xcp_short_download_len;
static int hf_xcp_short_download_reserved;
static int hf_xcp_short_download_address_extension;
static int hf_xcp_short_download_address;
static int hf_xcp_short_download_data_elements;

static int hf_xcp_modify_bits_shift_value;
static int hf_xcp_modify_bits_and_mask;
static int hf_xcp_modify_bits_xor_mask;

static int hf_xcp_set_cal_page_mode_flags;
static int hf_xcp_set_cal_page_ecu;
static int hf_xcp_set_cal_page_xcp;
static int hf_xcp_set_cal_page_x2;
static int hf_xcp_set_cal_page_x3;
static int hf_xcp_set_cal_page_x4;
static int hf_xcp_set_cal_page_x5;
static int hf_xcp_set_cal_page_x6;
static int hf_xcp_set_cal_page_all;

static int hf_xcp_set_cal_page_data_segment_num;
static int hf_xcp_set_cal_page_data_page_num;

static int hf_xcp_get_cal_page_access_mode;
static int hf_xcp_get_cal_page_data_segment_num;

static int hf_xcp_get_segment_info_mode;
static int hf_xcp_get_segment_info_segment_number;
static int hf_xcp_get_segment_info_segment_info;
static int hf_xcp_get_segment_info_mapping_index;

static int hf_xcp_get_page_info_reserved;
static int hf_xcp_get_page_info_segment_number;
static int hf_xcp_get_page_info_page_number;

static int hf_xcp_set_segment_mode_flags;
static int hf_xcp_set_segment_mode_freeze;
static int hf_xcp_set_segment_mode_x1;
static int hf_xcp_set_segment_mode_x2;
static int hf_xcp_set_segment_mode_x3;
static int hf_xcp_set_segment_mode_x4;
static int hf_xcp_set_segment_mode_x5;
static int hf_xcp_set_segment_mode_x6;
static int hf_xcp_set_segment_mode_x7;
static int hf_xcp_set_segment_mode_segment_number;

static int hf_xcp_get_segment_mode_reserved;
static int hf_xcp_get_segment_mode_segment_number;

static int hf_xcp_copy_cal_page_segment_num_src;
static int hf_xcp_copy_cal_page_page_num_src;
static int hf_xcp_copy_cal_page_segment_num_dst;
static int hf_xcp_copy_cal_page_page_num_dst;

static int hf_xcp_set_daq_ptr_reserved;
static int hf_xcp_set_daq_ptr_daq_list_num;
static int hf_xcp_set_daq_ptr_odt_entry;
static int hf_xcp_set_daq_ptr_odt_entry_num;

static int hf_xcp_write_daq_bit_offset;
static int hf_xcp_write_daq_size_of_daq_element;
static int hf_xcp_write_daq_address_extension;
static int hf_xcp_write_daq_address;

static int hf_xcp_set_daq_list_mode_flags;
static int hf_xcp_set_daq_list_mode_x0;
static int hf_xcp_set_daq_list_mode_direction;
static int hf_xcp_set_daq_list_mode_x2;
static int hf_xcp_set_daq_list_mode_x3;
static int hf_xcp_set_daq_list_mode_timestamp;
static int hf_xcp_set_daq_list_mode_pid_off;
static int hf_xcp_set_daq_list_mode_x6;
static int hf_xcp_set_daq_list_mode_x7;
static int hf_xcp_set_daq_list_mode_daq_list_num;
static int hf_xcp_set_daq_list_mode_event_channel_num;
static int hf_xcp_set_daq_list_mode_transmission_rate_prescaler;
static int hf_xcp_set_daq_list_mode_daq_list_prio;

static int hf_xcp_get_daq_list_mode_reserved;
static int hf_xcp_get_daq_list_mode_daq_list_num;

static int hf_xcp_start_stop_daq_list_mode;
static int hf_xcp_start_stop_daq_list_daq_list_num;

static int hf_xcp_get_daq_event_info_event_channel_num;

static int hf_xcp_alloc_daq_daq_count;

static int hf_xcp_alloc_odt_odt_count;

static int hf_xcp_alloc_odt_entry_odt_num;
static int hf_xcp_alloc_odt_entry_odt_entries_count;

static int hf_xcp_program_clear_mode;
static int hf_xcp_program_clear_reserved;
static int hf_xcp_program_clear_clear_range;

static int hf_xcp_get_sector_info_mode;
static int hf_xcp_get_sector_info_sector_number;

static int hf_xcp_program_prepare_not_used;
static int hf_xcp_program_prepare_code_size;

static int hf_xcp_program_format_compression;
static int hf_xcp_program_format_encryption_mode;
static int hf_xcp_program_format_programming_method;
static int hf_xcp_program_format_access_method;

static int hf_xcp_program_verify_verification_mode;
static int hf_xcp_program_verify_verification_type;
static int hf_xcp_program_verify_verification_value;

/* Only used with DTO */
/*static int hf_xcp_daq;
static int hf_xcp_timestamp;
static int hf_xcp_data;
*/

static gint ett_xcp;
static gint ett_xcp_set_request_mode;
static gint ett_xcp_set_cal_page_mode;
static gint ett_xcp_set_segment_mode;
static gint ett_xcp_set_daq_list_mode;

static gint global_address_granularity_value = 0;
static gint global_max_cto = 0;
/*static gint global_max_dto = 0;
*/

static void
dissect_xcp_cmd_request(proto_tree *xcp_tree, tvbuff_t *tvb, guint pid, gint *offset)
{
    if(pid == CMD_CONNECT)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_connection_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_ID)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_identification_type, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_SET_REQUEST)
    {
        static int* const mode_bits[] = {
            &hf_xcp_set_request_store_cal_req_flag,
            &hf_xcp_set_request_store_daq_req_flag,
            &hf_xcp_set_request_clear_daq_req_flag,
            &hf_xcp_set_request_x3,
            &hf_xcp_set_request_x4,
            &hf_xcp_set_request_x5,
            &hf_xcp_set_request_x6,
            &hf_xcp_set_request_x7,
            NULL
        };

        proto_tree_add_bitmask(xcp_tree, tvb, *offset, hf_xcp_set_request_mode_flags, ett_xcp_set_request_mode, mode_bits, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_request_session_configuration_id, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2; 
    }
    else if(pid == CMD_GET_SEED)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_seed_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_seed_resource, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_UNLOCK)
    {
        guint8 seed_length;

        seed_length = tvb_get_guint8(tvb, *offset);
        proto_tree_add_item(xcp_tree, hf_xcp_unlock_seed_len, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;

        if(seed_length != 0x00)
        {
            proto_tree_add_item(xcp_tree, hf_xcp_unlock_seed, tvb, *offset, seed_length, ENC_ASCII);
            *offset += seed_length;            
        }
    }
    else if(pid == CMD_SET_MTA)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_set_mta_reserved, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_set_mta_address_extension, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_mta_address, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 14;
    }
    else if(pid == CMD_UPLOAD)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_upload_number_data_element, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_SHORT_UPLOAD)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_short_upload_number_data_element, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_upload_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_upload_address_extension, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_upload_address, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;
    }
    else if(pid == CMD_BUILD_CHECKSUM)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_build_checksum_reserved, tvb, *offset, 3, ENC_BIG_ENDIAN);
        *offset += 3;
        proto_tree_add_item(xcp_tree, hf_xcp_build_checksum_block_size, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;
    }
    else if(pid == CMD_TRANSPORT_LAYER_CMD)
    {
        /* TODO: Add subcommand parsing */
        proto_tree_add_item(xcp_tree, hf_xcp_transport_layer_cmd_subcommand, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_USER_CMD)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_user_cmd_subcommand, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_DOWNLOAD || pid == CMD_DOWNLOAD_NEXT || pid == CMD_PROGRAM || pid == CMD_PROGRAM_NEXT)
    {
        guint8 data_elements_length;

        data_elements_length = tvb_get_guint8(tvb, *offset);
        proto_tree_add_item(xcp_tree, hf_xcp_download_number_data_elements, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;

        if(global_address_granularity_value > 2)
        {
            guint8 alignment_length = global_address_granularity_value - 2;
            proto_tree_add_item(xcp_tree, hf_xcp_download_alignment, tvb, *offset, alignment_length, ENC_BIG_ENDIAN);
            *offset += alignment_length;
        }

        if(data_elements_length)
        {
            proto_tree_add_item(xcp_tree, hf_xcp_download_data_elements, tvb, *offset, data_elements_length, ENC_BIG_ENDIAN);
            *offset += data_elements_length;
        }
    }
    else if(pid == CMD_DOWNLOAD_MAX || pid == CMD_PROGRAM_MAX)
    {
        guint8 data_elements_length;

        if(global_address_granularity_value > 1)
        {
            guint8 alignment_length = global_address_granularity_value - 1;
            proto_tree_add_item(xcp_tree, hf_xcp_download_alignment, tvb, *offset, alignment_length, ENC_BIG_ENDIAN);
            *offset += alignment_length;
        }

        data_elements_length = global_max_cto;
        if(data_elements_length)
        {
            proto_tree_add_item(xcp_tree, hf_xcp_download_data_elements, tvb, *offset, data_elements_length, ENC_BIG_ENDIAN);
            *offset += data_elements_length;
        }
    }
    else if(pid == CMD_SHORT_DOWNLOAD)
    {
        guint8 data_elements_length;
        
        data_elements_length = tvb_get_guint8(tvb, *offset);
        proto_tree_add_item(xcp_tree, hf_xcp_short_download_len, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_download_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_download_address_extension, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_short_download_address, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;

        if(data_elements_length != 0)
        {
            proto_tree_add_item(xcp_tree, hf_xcp_short_download_data_elements, tvb, *offset, data_elements_length, ENC_ASCII);
            *offset += data_elements_length;
        }
    }
    else if(pid == CMD_MODIFY_BITS)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_modify_bits_shift_value, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_modify_bits_and_mask, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_modify_bits_xor_mask, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_SET_CAL_PAGE)
    {
        static int* const mode_bits[] = {
            &hf_xcp_set_cal_page_ecu,
            &hf_xcp_set_cal_page_xcp,
            &hf_xcp_set_cal_page_x2,
            &hf_xcp_set_cal_page_x3,
            &hf_xcp_set_cal_page_x4,
            &hf_xcp_set_cal_page_x5,
            &hf_xcp_set_cal_page_x6,
            &hf_xcp_set_cal_page_all,
            NULL
        };

        proto_tree_add_bitmask(xcp_tree, tvb, *offset, hf_xcp_set_cal_page_mode_flags, ett_xcp_set_cal_page_mode, mode_bits, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_cal_page_data_segment_num, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_cal_page_data_page_num, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_CAL_PAGE)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_cal_page_access_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_cal_page_data_segment_num, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_SEGMENT_INFO)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_info_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_info_segment_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_info_segment_info, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_info_mapping_index, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;        
    }
    else if(pid == CMD_GET_PAGE_INFO)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_page_info_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_page_info_segment_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_page_info_page_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_SET_SEGMENT_MODE)
    {
        static int* const mode_bits[] = {
            &hf_xcp_set_segment_mode_freeze,
            &hf_xcp_set_segment_mode_x1,
            &hf_xcp_set_segment_mode_x2,
            &hf_xcp_set_segment_mode_x3,
            &hf_xcp_set_segment_mode_x4,
            &hf_xcp_set_segment_mode_x5,
            &hf_xcp_set_segment_mode_x6,
            &hf_xcp_set_segment_mode_x7,
            NULL
        };

        proto_tree_add_bitmask(xcp_tree, tvb, *offset, hf_xcp_set_segment_mode_flags, ett_xcp_set_segment_mode, mode_bits, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_segment_mode_segment_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_SEGMENT_MODE)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_segment_mode_segment_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_COPY_CAL_PAGE)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_copy_cal_page_segment_num_src, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_copy_cal_page_page_num_src, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_copy_cal_page_segment_num_dst, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_copy_cal_page_page_num_dst, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_SET_DAQ_PTR)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_ptr_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_ptr_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_ptr_odt_entry, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_ptr_odt_entry_num, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_WRITE_DAQ)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_write_daq_bit_offset, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_write_daq_size_of_daq_element, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_write_daq_address_extension, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_write_daq_address, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;
    }
    else if(pid == CMD_SET_DAQ_LIST_MODE)
    {
        static int* const mode_bits[] = {
            &hf_xcp_set_daq_list_mode_x0,
            &hf_xcp_set_daq_list_mode_direction,
            &hf_xcp_set_daq_list_mode_x2,
            &hf_xcp_set_daq_list_mode_x3,
            &hf_xcp_set_daq_list_mode_timestamp,
            &hf_xcp_set_daq_list_mode_pid_off,
            &hf_xcp_set_daq_list_mode_x6,
            &hf_xcp_set_daq_list_mode_x7,
            NULL
        };

        proto_tree_add_bitmask(xcp_tree, tvb, *offset, hf_xcp_set_daq_list_mode_flags, ett_xcp_set_daq_list_mode, mode_bits, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_list_mode_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_list_mode_event_channel_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_list_mode_transmission_rate_prescaler, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_set_daq_list_mode_daq_list_prio, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_DAQ_LIST_MODE || pid == CMD_GET_DAQ_LIST_INFO || pid == CMD_CLEAR_DAQ_LIST)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_START_STOP_DAQ_LIST)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_start_stop_daq_list_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_start_stop_daq_list_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_START_STOP_SYNCH)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_start_stop_daq_list_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_GET_DAQ_EVENT_INFO)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_event_info_event_channel_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_ALLOC_DAQ)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_alloc_daq_daq_count, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_ALLOC_ODT)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_alloc_odt_odt_count, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_ALLOC_ODT_ENTRY)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_reserved, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_daq_list_mode_daq_list_num, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_alloc_odt_entry_odt_num, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_alloc_odt_entry_odt_entries_count, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_PROGRAM_CLEAR)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_program_clear_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_clear_reserved, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_program_clear_clear_range, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;
    }
    else if(pid == CMD_GET_SECTOR_INFO)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_get_sector_info_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_get_sector_info_sector_number, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_PROGRAM_PREPARE)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_program_prepare_not_used, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_prepare_code_size, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
    }
    else if(pid == CMD_PROGRAM_FORMAT)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_program_format_compression, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_format_encryption_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_format_programming_method, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_format_access_method, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
    }
    else if(pid == CMD_PROGRAM_VERIFY)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_program_verify_verification_mode, tvb, *offset, 1, ENC_BIG_ENDIAN);
        *offset += 1;
        proto_tree_add_item(xcp_tree, hf_xcp_program_verify_verification_type, tvb, *offset, 2, ENC_BIG_ENDIAN);
        *offset += 2;
        proto_tree_add_item(xcp_tree, hf_xcp_program_verify_verification_value, tvb, *offset, 4, ENC_BIG_ENDIAN);
        *offset += 4;
    }
}

static int
dissect_xcp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree _U_, void *data _U_)
{
    proto_tree *xcp_tree;
    proto_item *ti;
    gint offset = 0;
    guint16 data_len;
    guint8 pid;
    gchar   *info;

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "XCP");
    /* Clear out stuff in the info column */
    col_clear(pinfo->cinfo,COL_INFO);

    ti = proto_tree_add_item(tree, proto_xcp, tvb, offset, -1, ENC_NA);
    xcp_tree = proto_item_add_subtree(ti, ett_xcp);

    data_len = tvb_get_ntohs(tvb, offset);
    proto_tree_add_item(xcp_tree, hf_xcp_len, tvb, offset, 2, ENC_BIG_ENDIAN);
    offset += 2;

    proto_tree_add_item(xcp_tree, hf_xcp_ctr, tvb, offset, 2, ENC_BIG_ENDIAN);
    offset += 2;

    pid = tvb_get_guint8(tvb, offset);
    proto_tree_add_item(xcp_tree, hf_xcp_pid, tvb, offset, 1, ENC_BIG_ENDIAN);
    offset += 1;

    info = wmem_strdup_printf(pinfo->pool, "%s",
                              val_to_str(pid, xcp_cmd, "Unknown PID (%d)"));

    proto_item_append_text(ti, ", %s", info);
    col_add_str(pinfo->cinfo, COL_INFO, info);

    dissect_xcp_cmd_request(xcp_tree, tvb, pid, &offset);

    /* Meaningful only for DTO */
    if (data_len > 1)
    {
    /* TODO: Check when FILL is required */
/*        proto_tree_add_item(xcp_tree, hf_xcp_fill, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;        
*/    }

    /* TODO: Perform data length check */
    /* TODO: Timestamp length check (1,2,4 bytes) is required */
/*    proto_tree_add_item(xcp_tree, hf_xcp_daq, tvb, offset, 2, ENC_BIG_ENDIAN);
    offset += 2;

    proto_tree_add_item(xcp_tree, hf_xcp_timestamp, tvb, offset, 1, ENC_BIG_ENDIAN);
    offset += 1;
*/

    return tvb_captured_length(tvb);
}

void
proto_register_xcp(void)
{
    static hf_register_info hf[] = {
        { &hf_xcp_len,
            {   "Payload Length", "xcp.len", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_ctr,
            {   "Counter", "xcp.ctr", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_pid,
            {   "PID", "xcp.pid", FT_UINT8, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_fill,
            {   "Fill", "xcp.fill", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_connection_mode,
            {   "Connection mode", "xcp.connection_mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_connection_mode), 0x0, NULL, HFILL } },

        { &hf_xcp_identification_type,
            {   "Identification type", "xcp.identification_type", FT_UINT8, BASE_DEC,  
                VALS(xcp_get_id_type), 0x0, NULL, HFILL } },

        { &hf_xcp_set_request_mode_flags,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_request_store_cal_req_flag,
            {   "Store CAL request flag", "xcp.set_request.store_cal_req", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_STORE_CAL_REQ, NULL, HFILL } },
        { &hf_xcp_set_request_store_daq_req_flag,
            {   "Store DAQ request flag", "xcp.set_request.store_daq_req", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_STORE_DAQ_REQ, NULL, HFILL } },
        { &hf_xcp_set_request_clear_daq_req_flag,
            {   "Clear DAQ request flag", "xcp.set_request.clear_daq_req", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_CLEAR_DAQ_REQ, NULL, HFILL } },
        { &hf_xcp_set_request_x3,
            {   "X3", "xcp.set_request.x3", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_X3, NULL, HFILL } },
        { &hf_xcp_set_request_x4,
            {   "X4", "xcp.set_request.x4", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_X4, NULL, HFILL } },
        { &hf_xcp_set_request_x5,
            {   "X5", "xcp.set_request.x5", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_X5, NULL, HFILL } },
        { &hf_xcp_set_request_x6,
            {   "X6", "xcp.set_request.x6", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_X6, NULL, HFILL } },
        { &hf_xcp_set_request_x7,
            {   "X7", "xcp.set_request.x7", FT_BOOLEAN, 8,  
                NULL, CMD_SET_REQUEST_X7, NULL, HFILL } },

        { &hf_xcp_set_request_session_configuration_id,
            {   "Session configuration ID", "xcp.session_configuration_id", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_seed_mode,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_get_seed_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_get_seed_resource,
            {   "Resource", "xcp.resource", FT_UINT8, BASE_DEC,  
                VALS(xcp_get_seed_resource), 0x0, NULL, HFILL } },

        { &hf_xcp_unlock_seed_len,
            {   "Seed length", "xcp.seed_len", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_unlock_seed,
            {   "Seed", "xcp.seed", FT_STRING, BASE_NONE,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_set_mta_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_mta_address_extension,
            {   "Address extension", "xcp.address_extension", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_mta_address,
            {   "Address", "xcp.address", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_upload_number_data_element,
            {   "Number of data element", "xcp.number_data_element", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_short_upload_number_data_element,
            {   "Number of data element", "xcp.number_data_element", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_upload_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_upload_address_extension,
            {   "Address_extension", "xcp.address_extension", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_upload_address,
            {   "Address", "xcp.address", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_build_checksum_reserved,
            {   "Reserved", "xcp.reserved", 3, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_build_checksum_block_size,
            {   "Block size", "xcp.block_size", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_transport_layer_cmd_subcommand,
            {   "Sub command", "xcp.subcommand", FT_UINT8, BASE_DEC,  
                VALS(xcp_transport_layer_cmd), 0x0, NULL, HFILL } },

        { &hf_xcp_user_cmd_subcommand,
            {   "Sub command", "xcp.subcommand", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_download_number_data_elements,
            {   "Number of data elements", "xcp.num_data_elements", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_download_alignment,
            {   "Alignment", "xcp.alignment", FT_STRING, BASE_NONE,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_download_data_elements,
            {   "Data elements", "xcp.data_elements", FT_STRING, BASE_NONE,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_short_download_len,
            {   "Length", "xcp.length", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_download_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_download_address_extension,
            {   "Address_extension", "xcp.address_extension", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_download_address,
            {   "Address", "xcp.address", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_short_download_data_elements,
            {   "Data elements", "xcp.data_elements", FT_STRING, BASE_NONE,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_modify_bits_shift_value,
            {   "Shift value", "xcp.shift_value", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_modify_bits_and_mask,
            {   "AND mask", "xcp.and_mask", FT_UINT16, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_modify_bits_xor_mask,
            {   "XOR mask", "xcp.xor_mask", FT_UINT16, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_set_cal_page_mode_flags,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_cal_page_ecu,
            {   "ECU", "xcp.set_cal_page.ecu", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_ECU, NULL, HFILL } },
        { &hf_xcp_set_cal_page_xcp,
            {   "XCP", "xcp.set_cal_page.xcp", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_XCP, NULL, HFILL } },
        { &hf_xcp_set_cal_page_x2,
            {   "X2", "xcp.set_cal_page.x2", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_X2, NULL, HFILL } },
        { &hf_xcp_set_cal_page_x3,
            {   "X3", "xcp.set_cal_page.x3", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_X3, NULL, HFILL } },
        { &hf_xcp_set_cal_page_x4,
            {   "X4", "xcp.set_cal_page.x4", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_X4, NULL, HFILL } },
        { &hf_xcp_set_cal_page_x5,
            {   "X5", "xcp.set_cal_page.x5", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_X5, NULL, HFILL } },
        { &hf_xcp_set_cal_page_x6,
            {   "X6", "xcp.set_cal_page.x6", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_X6, NULL, HFILL } },
        { &hf_xcp_set_cal_page_all,
            {   "All", "xcp.set_cal_page.all", FT_BOOLEAN, 8,  
                NULL, CMD_SET_CAL_PAGE_ALL, NULL, HFILL } },
        { &hf_xcp_set_cal_page_data_segment_num,
            {   "Data segment number", "xcp.data_segment_num", FT_UINT8, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_cal_page_data_page_num,
            {   "Data page number", "xcp.data_page_num", FT_UINT8, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_cal_page_access_mode,
            {   "Access mode", "xcp.access_mode", FT_UINT8, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_cal_page_data_segment_num,
            {   "Data segment number", "xcp.data_segment_num", FT_UINT8, BASE_HEX,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_segment_info_mode,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_get_segment_info_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_get_segment_info_segment_number,
            {   "Segment number", "xcp.segment_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_segment_info_segment_info,
            {   "Segment info", "xcp.segment_info", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_segment_info_mapping_index,
            {   "Mapping index", "xcp.mapping_index", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_page_info_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_page_info_segment_number,
            {   "Segment number", "xcp.segment_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_page_info_page_number,
            {   "Page number", "xcp.page_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_set_segment_mode_flags,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_freeze,
            {   "Freeze", "xcp.set_segment_mode.freeze", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_FREEZE, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x1,
            {   "X1", "xcp.set_segment_mode.x1", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X1, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x2,
            {   "X2", "xcp.set_segment_mode.x2", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X2, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x3,
            {   "X3", "xcp.set_segment_mode.x3", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X3, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x4,
            {   "X4", "xcp.set_segment_mode.x4", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X4, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x5,
            {   "X5", "xcp.set_segment_mode.x5", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X5, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x6,
            {   "X6", "xcp.set_segment_mode.x6", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X6, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_x7,
            {   "X7", "xcp.set_segment_mode.x7", FT_BOOLEAN, 8,  
                NULL, CMD_SET_SEGMENT_MODE_X7, NULL, HFILL } },
        { &hf_xcp_set_segment_mode_segment_number,
            {   "Segment number", "xcp.segment_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_segment_mode_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_segment_mode_segment_number,
            {   "Segment number", "xcp.segment_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_copy_cal_page_segment_num_src,
            {   "Segment source", "xcp.segment_src", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_copy_cal_page_page_num_src,
            {   "Page source", "xcp.page_src", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_copy_cal_page_segment_num_dst,
            {   "Segment destination", "xcp.segment_dst", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_copy_cal_page_page_num_dst,
            {   "Page destination", "xcp.page_dst", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_set_daq_ptr_reserved,
            {   "Reserved", "xcp.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_ptr_daq_list_num,
            {   "DAQ list number", "xcp.daq_list_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_ptr_odt_entry,
            {   "ODT entry", "xcp.odt_entry", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_ptr_odt_entry_num,
            {   "ODT entry number", "xcp.odt_entry_num", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_write_daq_bit_offset,
            {   "Bit offset", "xcp.bit_offset", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_write_daq_size_of_daq_element,
            {   "Size of DAQ element", "xcp.size_of_daq_element", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_write_daq_address_extension,
            {   "Address extension", "xcp.address_extension", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_write_daq_address,
            {   "Address", "xcp.address", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_set_daq_list_mode_flags,
            {   "Mode", "xcp.mode", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_x0,
            {   "X0", "xcp.set_daq_list_mode.x0", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_X0, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_direction,
            {   "Direction", "xcp.set_daq_list_mode.direction", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_DIRECTION, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_x2,
            {   "X2", "xcp.set_daq_list_mode.x2", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_X2, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_x3,
            {   "X3", "xcp.set_daq_list_mode.x3", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_X3, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_timestamp,
            {   "Timestamp", "xcp.set_daq_list_mode.timestamp", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_TIMESTAMP, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_pid_off,
            {   "PID Off", "xcp.set_daq_list_mode.pid_off", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_PID_OFF, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_x6,
            {   "X6", "xcp.set_daq_list_mode.X6", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_X6, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_x7,
            {   "X7", "xcp.set_daq_list_mode.X7", FT_BOOLEAN, 8,  
                NULL, CMD_SET_DAQ_LIST_MODE_X7, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_daq_list_num,
            {   "DAQ list number", "xcp.set_daq_list_mode.daq_list_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_event_channel_num,
            {   "Event channel number", "xcp.set_daq_list_mode.event_channel_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_transmission_rate_prescaler,
            {   "Transmission rate prescaler", "xcp.set_daq_list_mode.transmission_rate_prescaler", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_set_daq_list_mode_daq_list_prio,
            {   "DAQ list priority", "xcp.set_daq_list_mode.daq_list_prio", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_daq_list_mode_reserved,
            {   "Reserved", "xcp.get_daq_list_mode.reserved", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_get_daq_list_mode_daq_list_num,
            {   "DAQ list number", "xcp.get_daq_list_mode.daq_list_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_start_stop_daq_list_mode,
            {   "Mode", "xcp.start_stop_daq_list.mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_start_stop_daq_list_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_start_stop_daq_list_daq_list_num,
            {   "DAQ list number", "xcp.start_stop_daq_list.daq_list_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_daq_event_info_event_channel_num,
            {   "Event channel number", "xcp.get_daq_event_info.event_channel_num", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_alloc_daq_daq_count,
            {   "DAQ count", "xcp.alloc_daq.daq_count", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_alloc_odt_odt_count,
            {   "ODT count", "xcp.alloc_odt.odt_count", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_alloc_odt_entry_odt_num,
            {   "ODT number", "xcp.alloc_odt_entry.odt_num", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_alloc_odt_entry_odt_entries_count,
            {   "ODT entries count", "xcp.alloc_odt_entry.odt_entries_count", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_program_clear_mode,
            {   "Mode", "xcp.program_clear.mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_program_clear_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_program_clear_reserved,
            {   "Reserved", "xcp.program_clear.reserved", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_clear_clear_range,
            {   "Clear range", "xcp.program_clear.clear_range", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_get_sector_info_mode,
            {   "Mode", "xcp.get_sector_info.mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_get_sector_info_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_get_sector_info_sector_number,
            {   "Sector number", "xcp.get_sector_info.sector_number", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_program_prepare_not_used,
            {   "Not used", "xcp.program_prepare.not_used", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_prepare_code_size,
            {   "Code size", "xcp.program_prepare.code_size", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_program_format_compression,
            {   "Compression", "xcp.program_format.compression", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_format_encryption_mode,
            {   "Encryption mode", "xcp.program_format.encryption_mode", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_format_programming_method,
            {   "Programming method", "xcp.program_format.programming_method", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_format_access_method,
            {   "Access method", "xcp.program_format.access_method", FT_UINT8, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },

        { &hf_xcp_program_verify_verification_mode,
            {   "Verification mode", "xcp.program_verify.verification_mode", FT_UINT8, BASE_DEC,  
                VALS(xcp_program_verify_verification_mode), 0x0, NULL, HFILL } },
        { &hf_xcp_program_verify_verification_type,
            {   "Verification type", "xcp.program_verify.verification_type", FT_UINT16, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
        { &hf_xcp_program_verify_verification_value,
            {   "Verification value", "xcp.program_verify.verification_value", FT_UINT32, BASE_DEC,  
                NULL, 0x0, NULL, HFILL } },
    };

    static gint *ett[] = {
        &ett_xcp,
        &ett_xcp_set_request_mode,
        &ett_xcp_set_cal_page_mode,
        &ett_xcp_set_segment_mode,
        &ett_xcp_set_daq_list_mode
    };

    proto_xcp = proto_register_protocol (
        "Universal Calibration Protocol", /* name        */
        "XCP",          /* short_name  */
        "xcp"           /* filter_name */
        );

    proto_register_field_array(proto_xcp, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));

}

void
proto_reg_handoff_xcp(void)
{
    static dissector_handle_t xcp_handle;

    xcp_handle = create_dissector_handle(dissect_xcp, proto_xcp);
    dissector_add_uint_range_with_preference("udp.port", XCP_PORT_RANGE, xcp_handle);
    dissector_add_uint_range_with_preference("tcp.port", XCP_PORT_RANGE, xcp_handle);

    module_t *xcp_module = prefs_register_protocol(proto_xcp, NULL);
    prefs_register_enum_preference(xcp_module, "address_granularity",
        "Address granularity",
        "Define the address granularity",
        &global_address_granularity_value,
        address_granularity, FALSE
        );
}