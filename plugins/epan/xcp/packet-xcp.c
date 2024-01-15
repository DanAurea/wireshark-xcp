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

/*static int hf_xcp_daq;
static int hf_xcp_timestamp;
static int hf_xcp_data;
*/
static gint ett_xcp;
static gint ett_xcp_set_request_mode;

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
    else if(pid == CMD_DOWNLOAD)
    {
        /* TODO: Add parsing */
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
    };

    static gint *ett[] = {
        &ett_xcp,
        &ett_xcp_set_request_mode
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
}