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

static int proto_xcp;

static int hf_xcp_len;
static int hf_xcp_ctr;
static int hf_xcp_pid;
static int hf_xcp_fill;
/*static int hf_xcp_daq;
static int hf_xcp_timestamp;
static int hf_xcp_data;
*/
static gint ett_xcp;

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

    if (data_len > 1)
    {
        proto_tree_add_item(xcp_tree, hf_xcp_fill, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;        
    }    

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
    };

    static gint *ett[] = {
        &ett_xcp
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