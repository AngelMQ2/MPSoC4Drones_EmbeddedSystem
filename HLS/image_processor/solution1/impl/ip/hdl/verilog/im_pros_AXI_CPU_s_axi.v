// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module im_pros_AXI_CPU_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 16,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    input  wire [13:0]                   imageIn_address0,
    input  wire                          imageIn_ce0,
    output wire [7:0]                    imageIn_q0,
    input  wire [13:0]                   imageOut_address0,
    input  wire                          imageOut_ce0,
    input  wire                          imageOut_we0,
    input  wire [7:0]                    imageOut_d0
);
//------------------------Address Info-------------------
// 0x4000 ~
// 0x7fff : Memory 'imageIn' (12288 * 8b)
//          Word n : bit [ 7: 0] - imageIn[4n]
//                   bit [15: 8] - imageIn[4n+1]
//                   bit [23:16] - imageIn[4n+2]
//                   bit [31:24] - imageIn[4n+3]
// 0x8000 ~
// 0xbfff : Memory 'imageOut' (12288 * 8b)
//          Word n : bit [ 7: 0] - imageOut[4n]
//                   bit [15: 8] - imageOut[4n+1]
//                   bit [23:16] - imageOut[4n+2]
//                   bit [31:24] - imageOut[4n+3]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_IMAGEIN_BASE  = 16'h4000,
    ADDR_IMAGEIN_HIGH  = 16'h7fff,
    ADDR_IMAGEOUT_BASE = 16'h8000,
    ADDR_IMAGEOUT_HIGH = 16'hbfff,
    WRIDLE             = 2'd0,
    WRDATA             = 2'd1,
    WRRESP             = 2'd2,
    WRRESET            = 2'd3,
    RDIDLE             = 2'd0,
    RDDATA             = 2'd1,
    RDRESET            = 2'd2,
    ADDR_BITS                = 16;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // memory signals
    wire [11:0]                   int_imageIn_address0;
    wire                          int_imageIn_ce0;
    wire                          int_imageIn_we0;
    wire [3:0]                    int_imageIn_be0;
    wire [31:0]                   int_imageIn_d0;
    wire [31:0]                   int_imageIn_q0;
    wire [11:0]                   int_imageIn_address1;
    wire                          int_imageIn_ce1;
    wire                          int_imageIn_we1;
    wire [3:0]                    int_imageIn_be1;
    wire [31:0]                   int_imageIn_d1;
    wire [31:0]                   int_imageIn_q1;
    reg                           int_imageIn_read;
    reg                           int_imageIn_write;
    reg  [1:0]                    int_imageIn_shift;
    wire [11:0]                   int_imageOut_address0;
    wire                          int_imageOut_ce0;
    wire                          int_imageOut_we0;
    wire [3:0]                    int_imageOut_be0;
    wire [31:0]                   int_imageOut_d0;
    wire [31:0]                   int_imageOut_q0;
    wire [11:0]                   int_imageOut_address1;
    wire                          int_imageOut_ce1;
    wire                          int_imageOut_we1;
    wire [3:0]                    int_imageOut_be1;
    wire [31:0]                   int_imageOut_d1;
    wire [31:0]                   int_imageOut_q1;
    reg                           int_imageOut_read;
    reg                           int_imageOut_write;
    reg  [1:0]                    int_imageOut_shift;

//------------------------Instantiation------------------
// int_imageIn
im_pros_AXI_CPU_s_axi_ram #(
    .BYTES    ( 4 ),
    .DEPTH    ( 3072 )
) int_imageIn (
    .clk0     ( ACLK ),
    .address0 ( int_imageIn_address0 ),
    .ce0      ( int_imageIn_ce0 ),
    .we0      ( int_imageIn_we0 ),
    .be0      ( int_imageIn_be0 ),
    .d0       ( int_imageIn_d0 ),
    .q0       ( int_imageIn_q0 ),
    .clk1     ( ACLK ),
    .address1 ( int_imageIn_address1 ),
    .ce1      ( int_imageIn_ce1 ),
    .we1      ( int_imageIn_we1 ),
    .be1      ( int_imageIn_be1 ),
    .d1       ( int_imageIn_d1 ),
    .q1       ( int_imageIn_q1 )
);
// int_imageOut
im_pros_AXI_CPU_s_axi_ram #(
    .BYTES    ( 4 ),
    .DEPTH    ( 3072 )
) int_imageOut (
    .clk0     ( ACLK ),
    .address0 ( int_imageOut_address0 ),
    .ce0      ( int_imageOut_ce0 ),
    .we0      ( int_imageOut_we0 ),
    .be0      ( int_imageOut_be0 ),
    .d0       ( int_imageOut_d0 ),
    .q0       ( int_imageOut_q0 ),
    .clk1     ( ACLK ),
    .address1 ( int_imageOut_address1 ),
    .ce1      ( int_imageOut_ce1 ),
    .we1      ( int_imageOut_we1 ),
    .be1      ( int_imageOut_be1 ),
    .d1       ( int_imageOut_d1 ),
    .q1       ( int_imageOut_q1 )
);


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA) && (!ar_hs);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (w_hs)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA) & !int_imageIn_read & !int_imageOut_read;
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
        end
        else if (int_imageIn_read) begin
            rdata <= int_imageIn_q1;
        end
        else if (int_imageOut_read) begin
            rdata <= int_imageOut_q1;
        end
    end
end


//------------------------Register logic-----------------

//------------------------Memory logic-------------------
// imageIn
assign int_imageIn_address0  = imageIn_address0 >> 2;
assign int_imageIn_ce0       = imageIn_ce0;
assign int_imageIn_we0       = 1'b0;
assign int_imageIn_be0       = 1'b0;
assign int_imageIn_d0        = 1'b0;
assign imageIn_q0            = int_imageIn_q0 >> (int_imageIn_shift * 8);
assign int_imageIn_address1  = ar_hs? raddr[13:2] : waddr[13:2];
assign int_imageIn_ce1       = ar_hs | (int_imageIn_write & WVALID);
assign int_imageIn_we1       = int_imageIn_write & w_hs;
assign int_imageIn_be1       = WSTRB;
assign int_imageIn_d1        = WDATA;
// imageOut
assign int_imageOut_address0 = imageOut_address0 >> 2;
assign int_imageOut_ce0      = imageOut_ce0;
assign int_imageOut_we0      = imageOut_we0;
assign int_imageOut_be0      = 1 << imageOut_address0[1:0];
assign int_imageOut_d0       = {4{imageOut_d0}};
assign int_imageOut_address1 = ar_hs? raddr[13:2] : waddr[13:2];
assign int_imageOut_ce1      = ar_hs | (int_imageOut_write & WVALID);
assign int_imageOut_we1      = int_imageOut_write & w_hs;
assign int_imageOut_be1      = WSTRB;
assign int_imageOut_d1       = WDATA;
// int_imageIn_read
always @(posedge ACLK) begin
    if (ARESET)
        int_imageIn_read <= 1'b0;
    else if (ACLK_EN) begin
        if (ar_hs && raddr >= ADDR_IMAGEIN_BASE && raddr <= ADDR_IMAGEIN_HIGH)
            int_imageIn_read <= 1'b1;
        else
            int_imageIn_read <= 1'b0;
    end
end

// int_imageIn_write
always @(posedge ACLK) begin
    if (ARESET)
        int_imageIn_write <= 1'b0;
    else if (ACLK_EN) begin
        if (aw_hs && AWADDR[ADDR_BITS-1:0] >= ADDR_IMAGEIN_BASE && AWADDR[ADDR_BITS-1:0] <= ADDR_IMAGEIN_HIGH)
            int_imageIn_write <= 1'b1;
        else if (w_hs)
            int_imageIn_write <= 1'b0;
    end
end

// int_imageIn_shift
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (imageIn_ce0)
            int_imageIn_shift <= imageIn_address0[1:0];
    end
end

// int_imageOut_read
always @(posedge ACLK) begin
    if (ARESET)
        int_imageOut_read <= 1'b0;
    else if (ACLK_EN) begin
        if (ar_hs && raddr >= ADDR_IMAGEOUT_BASE && raddr <= ADDR_IMAGEOUT_HIGH)
            int_imageOut_read <= 1'b1;
        else
            int_imageOut_read <= 1'b0;
    end
end

// int_imageOut_write
always @(posedge ACLK) begin
    if (ARESET)
        int_imageOut_write <= 1'b0;
    else if (ACLK_EN) begin
        if (aw_hs && AWADDR[ADDR_BITS-1:0] >= ADDR_IMAGEOUT_BASE && AWADDR[ADDR_BITS-1:0] <= ADDR_IMAGEOUT_HIGH)
            int_imageOut_write <= 1'b1;
        else if (w_hs)
            int_imageOut_write <= 1'b0;
    end
end

// int_imageOut_shift
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (imageOut_ce0)
            int_imageOut_shift <= imageOut_address0[1:0];
    end
end


endmodule


`timescale 1ns/1ps

module im_pros_AXI_CPU_s_axi_ram
#(parameter
    BYTES  = 4,
    DEPTH  = 256,
    AWIDTH = log2(DEPTH)
) (
    input  wire               clk0,
    input  wire [AWIDTH-1:0]  address0,
    input  wire               ce0,
    input  wire               we0,
    input  wire [BYTES-1:0]   be0,
    input  wire [BYTES*8-1:0] d0,
    output reg  [BYTES*8-1:0] q0,
    input  wire               clk1,
    input  wire [AWIDTH-1:0]  address1,
    input  wire               ce1,
    input  wire               we1,
    input  wire [BYTES-1:0]   be1,
    input  wire [BYTES*8-1:0] d1,
    output reg  [BYTES*8-1:0] q1
);
//------------------------Local signal-------------------
reg  [BYTES*8-1:0] mem[0:DEPTH-1];
//------------------------Task and function--------------
function integer log2;
    input integer x;
    integer n, m;
begin
    n = 1;
    m = 2;
    while (m < x) begin
        n = n + 1;
        m = m * 2;
    end
    log2 = n;
end
endfunction
//------------------------Body---------------------------
// read port 0
always @(posedge clk0) begin
    if (ce0) q0 <= mem[address0];
end

// read port 1
always @(posedge clk1) begin
    if (ce1) q1 <= mem[address1];
end

genvar i;
generate
    for (i = 0; i < BYTES; i = i + 1) begin : gen_write
        // write port 0
        always @(posedge clk0) begin
            if (ce0 & we0 & be0[i]) begin
                mem[address0][8*i+7:8*i] <= d0[8*i+7:8*i];
            end
        end
        // write port 1
        always @(posedge clk1) begin
            if (ce1 & we1 & be1[i]) begin
                mem[address1][8*i+7:8*i] <= d1[8*i+7:8*i];
            end
        end
    end
endgenerate

endmodule

