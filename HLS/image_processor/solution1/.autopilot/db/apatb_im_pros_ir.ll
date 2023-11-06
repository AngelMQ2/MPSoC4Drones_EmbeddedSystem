; ModuleID = '/home/acerpc/OneDrive/SDU/EmbeddedSystems/assigment2/HLS/image_processor/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%struct.ap_uint = type { %struct.ap_int_base }
%struct.ap_int_base = type { %struct.ssdm_int }
%struct.ssdm_int = type { i8 }

; Function Attrs: noinline
define void @apatb_im_pros_ir([128 x %struct.ap_uint]* %imageIn, [128 x %struct.ap_uint]* %imageOut) local_unnamed_addr #0 {
entry:
  %malloccall = tail call i8* @malloc(i64 12288)
  %imageIn_copy = bitcast i8* %malloccall to [96 x [128 x %struct.ap_uint]]*
  %malloccall1 = tail call i8* @malloc(i64 12288)
  %imageOut_copy = bitcast i8* %malloccall1 to [96 x [128 x %struct.ap_uint]]*
  %0 = bitcast [128 x %struct.ap_uint]* %imageIn to [96 x [128 x %struct.ap_uint]]*
  %1 = bitcast [128 x %struct.ap_uint]* %imageOut to [96 x [128 x %struct.ap_uint]]*
  call fastcc void @copy_in([96 x [128 x %struct.ap_uint]]* %0, [96 x [128 x %struct.ap_uint]]* %imageIn_copy, [96 x [128 x %struct.ap_uint]]* %1, [96 x [128 x %struct.ap_uint]]* %imageOut_copy)
  %2 = getelementptr inbounds [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %imageIn_copy, i32 0, i32 0
  %3 = getelementptr inbounds [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %imageOut_copy, i32 0, i32 0
  call void @apatb_im_pros_hw([128 x %struct.ap_uint]* %2, [128 x %struct.ap_uint]* %3)
  call fastcc void @copy_out([96 x [128 x %struct.ap_uint]]* %0, [96 x [128 x %struct.ap_uint]]* %imageIn_copy, [96 x [128 x %struct.ap_uint]]* %1, [96 x [128 x %struct.ap_uint]]* %imageOut_copy)
  tail call void @free(i8* %malloccall)
  tail call void @free(i8* %malloccall1)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: noinline
define internal fastcc void @copy_in([96 x [128 x %struct.ap_uint]]*, [96 x [128 x %struct.ap_uint]]* noalias, [96 x [128 x %struct.ap_uint]]*, [96 x [128 x %struct.ap_uint]]* noalias) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a96a128struct.ap_uint([96 x [128 x %struct.ap_uint]]* %1, [96 x [128 x %struct.ap_uint]]* %0)
  call fastcc void @onebyonecpy_hls.p0a96a128struct.ap_uint([96 x [128 x %struct.ap_uint]]* %3, [96 x [128 x %struct.ap_uint]]* %2)
  ret void
}

; Function Attrs: noinline
define internal fastcc void @onebyonecpy_hls.p0a96a128struct.ap_uint([96 x [128 x %struct.ap_uint]]* noalias, [96 x [128 x %struct.ap_uint]]* noalias) unnamed_addr #2 {
entry:
  %2 = icmp eq [96 x [128 x %struct.ap_uint]]* %0, null
  %3 = icmp eq [96 x [128 x %struct.ap_uint]]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop.split, %copy
  %for.loop.idx16 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop.split ]
  br label %for.loop2

for.loop2:                                        ; preds = %for.loop.head1, %for.loop
  %for.loop.idx315 = phi i64 [ 0, %for.loop ], [ %for.loop.idx3.next, %for.loop.head1 ]
  %dst.addr57 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %0, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315
  %src.addr68 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %1, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315
  %5 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %1, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0, i32 0, i32 0
  %6 = call i1 @fpga_fifo_exist_1(i8* %5)
  br i1 %6, label %7, label %8

; <label>:7:                                      ; preds = %for.loop2
  call fastcc void @streamcpy_hls.p0struct.ap_uint(%struct.ap_uint* %dst.addr57, %struct.ap_uint* %src.addr68)
  br label %for.loop.head1

; <label>:8:                                      ; preds = %for.loop2
  %src.addr6.09 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %1, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0
  %dst.addr5.010 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %0, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0
  %9 = call i1 @fpga_fifo_exist_1(i8* %5)
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %8
  call fastcc void @streamcpy_hls.p0struct.ap_int_base(%struct.ap_int_base* %dst.addr5.010, %struct.ap_int_base* %src.addr6.09)
  br label %for.loop.head1

; <label>:11:                                     ; preds = %8
  %src.addr6.0.011 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %1, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0, i32 0
  %dst.addr5.0.012 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %0, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0, i32 0
  %12 = call i1 @fpga_fifo_exist_1(i8* %5)
  br i1 %12, label %13, label %14

; <label>:13:                                     ; preds = %11
  call fastcc void @streamcpy_hls.p0struct.ssdm_int(%struct.ssdm_int* %dst.addr5.0.012, %struct.ssdm_int* %src.addr6.0.011)
  br label %for.loop.head1

; <label>:14:                                     ; preds = %11
  %dst.addr5.0.0.014 = getelementptr [96 x [128 x %struct.ap_uint]], [96 x [128 x %struct.ap_uint]]* %0, i64 0, i64 %for.loop.idx16, i64 %for.loop.idx315, i32 0, i32 0, i32 0
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %dst.addr5.0.0.014, i8* align 1 %5, i64 1, i1 false)
  br label %for.loop.head1

for.loop.head1:                                   ; preds = %14, %13, %10, %7
  %for.loop.idx3.next = add nuw nsw i64 %for.loop.idx315, 1
  %exitcond = icmp ne i64 %for.loop.idx3.next, 128
  br i1 %exitcond, label %for.loop2, label %for.loop.split

for.loop.split:                                   ; preds = %for.loop.head1
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx16, 1
  %exitcond17 = icmp ne i64 %for.loop.idx.next, 96
  br i1 %exitcond17, label %for.loop, label %ret

ret:                                              ; preds = %for.loop.split, %entry
  ret void
}

declare i1 @fpga_fifo_exist_1(i8*) local_unnamed_addr

; Function Attrs: argmemonly noinline
define internal fastcc void @streamcpy_hls.p0struct.ap_uint(%struct.ap_uint* noalias nocapture, %struct.ap_uint* noalias nocapture) unnamed_addr #3 {
entry:
  %2 = alloca %struct.ap_uint
  br label %empty

empty:                                            ; preds = %push, %entry
  %3 = bitcast %struct.ap_uint* %1 to i8*
  %4 = call i1 @fpga_fifo_not_empty_1(i8* %3)
  br i1 %4, label %push, label %ret

push:                                             ; preds = %empty
  %5 = bitcast %struct.ap_uint* %2 to i8*
  %6 = bitcast %struct.ap_uint* %1 to i8*
  call void @fpga_fifo_pop_1(i8* %5, i8* %6)
  %7 = load volatile %struct.ap_uint, %struct.ap_uint* %2
  %8 = bitcast %struct.ap_uint* %2 to i8*
  %9 = bitcast %struct.ap_uint* %0 to i8*
  call void @fpga_fifo_push_1(i8* %8, i8* %9)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  %10 = getelementptr inbounds %struct.ap_uint, %struct.ap_uint* %1, i32 0, i32 0, i32 0, i32 0
  %11 = getelementptr inbounds %struct.ap_uint, %struct.ap_uint* %0, i32 0, i32 0, i32 0, i32 0
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %11, i8* align 1 %10, i64 1, i1 false)
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #4

; Function Attrs: argmemonly noinline
define internal fastcc void @streamcpy_hls.p0struct.ap_int_base(%struct.ap_int_base* noalias nocapture, %struct.ap_int_base* noalias nocapture) unnamed_addr #3 {
entry:
  %2 = alloca %struct.ap_int_base
  br label %empty

empty:                                            ; preds = %push, %entry
  %3 = bitcast %struct.ap_int_base* %1 to i8*
  %4 = call i1 @fpga_fifo_not_empty_1(i8* %3)
  br i1 %4, label %push, label %ret

push:                                             ; preds = %empty
  %5 = bitcast %struct.ap_int_base* %2 to i8*
  %6 = bitcast %struct.ap_int_base* %1 to i8*
  call void @fpga_fifo_pop_1(i8* %5, i8* %6)
  %7 = load volatile %struct.ap_int_base, %struct.ap_int_base* %2
  %8 = bitcast %struct.ap_int_base* %2 to i8*
  %9 = bitcast %struct.ap_int_base* %0 to i8*
  call void @fpga_fifo_push_1(i8* %8, i8* %9)
  br label %empty, !llvm.loop !7

ret:                                              ; preds = %empty
  %10 = getelementptr inbounds %struct.ap_int_base, %struct.ap_int_base* %1, i32 0, i32 0, i32 0
  %11 = getelementptr inbounds %struct.ap_int_base, %struct.ap_int_base* %0, i32 0, i32 0, i32 0
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %11, i8* align 1 %10, i64 1, i1 false)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @streamcpy_hls.p0struct.ssdm_int(%struct.ssdm_int* noalias nocapture, %struct.ssdm_int* noalias nocapture) unnamed_addr #3 {
entry:
  %2 = alloca %struct.ssdm_int
  br label %empty

empty:                                            ; preds = %push, %entry
  %3 = bitcast %struct.ssdm_int* %1 to i8*
  %4 = call i1 @fpga_fifo_not_empty_1(i8* %3)
  br i1 %4, label %push, label %ret

push:                                             ; preds = %empty
  %5 = bitcast %struct.ssdm_int* %2 to i8*
  %6 = bitcast %struct.ssdm_int* %1 to i8*
  call void @fpga_fifo_pop_1(i8* %5, i8* %6)
  %7 = load volatile %struct.ssdm_int, %struct.ssdm_int* %2
  %8 = bitcast %struct.ssdm_int* %2 to i8*
  %9 = bitcast %struct.ssdm_int* %0 to i8*
  call void @fpga_fifo_push_1(i8* %8, i8* %9)
  br label %empty, !llvm.loop !8

ret:                                              ; preds = %empty
  %10 = getelementptr inbounds %struct.ssdm_int, %struct.ssdm_int* %1, i32 0, i32 0
  %11 = getelementptr inbounds %struct.ssdm_int, %struct.ssdm_int* %0, i32 0, i32 0
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %11, i8* align 1 %10, i64 1, i1 false)
  ret void
}

; Function Attrs: noinline
define internal fastcc void @copy_out([96 x [128 x %struct.ap_uint]]*, [96 x [128 x %struct.ap_uint]]* noalias, [96 x [128 x %struct.ap_uint]]*, [96 x [128 x %struct.ap_uint]]* noalias) unnamed_addr #5 {
entry:
  call fastcc void @onebyonecpy_hls.p0a96a128struct.ap_uint([96 x [128 x %struct.ap_uint]]* %0, [96 x [128 x %struct.ap_uint]]* %1)
  call fastcc void @onebyonecpy_hls.p0a96a128struct.ap_uint([96 x [128 x %struct.ap_uint]]* %2, [96 x [128 x %struct.ap_uint]]* %3)
  ret void
}

declare void @free(i8*) local_unnamed_addr

declare void @apatb_im_pros_hw([128 x %struct.ap_uint]*, [128 x %struct.ap_uint]*)

define void @im_pros_hw_stub_wrapper([128 x %struct.ap_uint]*, [128 x %struct.ap_uint]*) #6 {
entry:
  %2 = bitcast [128 x %struct.ap_uint]* %0 to [96 x [128 x %struct.ap_uint]]*
  %3 = bitcast [128 x %struct.ap_uint]* %1 to [96 x [128 x %struct.ap_uint]]*
  call void @copy_out([96 x [128 x %struct.ap_uint]]* null, [96 x [128 x %struct.ap_uint]]* %2, [96 x [128 x %struct.ap_uint]]* null, [96 x [128 x %struct.ap_uint]]* %3)
  %4 = bitcast [96 x [128 x %struct.ap_uint]]* %2 to [128 x %struct.ap_uint]*
  %5 = bitcast [96 x [128 x %struct.ap_uint]]* %3 to [128 x %struct.ap_uint]*
  call void @im_pros_hw_stub([128 x %struct.ap_uint]* %4, [128 x %struct.ap_uint]* %5)
  call void @copy_in([96 x [128 x %struct.ap_uint]]* null, [96 x [128 x %struct.ap_uint]]* %2, [96 x [128 x %struct.ap_uint]]* null, [96 x [128 x %struct.ap_uint]]* %3)
  ret void
}

declare void @im_pros_hw_stub([128 x %struct.ap_uint]*, [128 x %struct.ap_uint]*)

declare i1 @fpga_fifo_not_empty_1(i8*)

declare void @fpga_fifo_pop_1(i8*, i8*)

declare void @fpga_fifo_push_1(i8*, i8*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { noinline "fpga.wrapper.func"="copyin" }
attributes #2 = { noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noinline "fpga.wrapper.func"="copyout" }
attributes #6 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
!7 = distinct !{!7, !6}
!8 = distinct !{!8, !6}
