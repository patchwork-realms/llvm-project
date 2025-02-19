; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 2
; Test i128 atomicrmw operations.
;
; RUN: llc < %s -mtriple=s390x-linux-gnu -mcpu=z15 | FileCheck %s
;
; Test expansion of AtomicRMW instructions, which assume a natural alignment.
; Note that the multiple regmoves inside the CDSG loops hopefully will go away
; when the new i128 support is added.

; Check register exchange.
define i128 @atomicrmw_xchg(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_xchg:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r12, %r15, 96(%r15)
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r14, 8(%r4)
; CHECK-NEXT:    lg %r0, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:    lgr %r1, %r14
; CHECK-NEXT:  .LBB0_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    lgr %r12, %r5
; CHECK-NEXT:    lgr %r13, %r4
; CHECK-NEXT:    cdsg %r12, %r0, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r13
; CHECK-NEXT:    lgr %r5, %r12
; CHECK-NEXT:    jl .LBB0_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r12, %r15, 96(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw xchg ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check addition of a variable.
define i128 @atomicrmw_add(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_add:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB1_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    algrk %r13, %r4, %r0
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    alcgr %r5, %r1
; CHECK-NEXT:    lgr %r12, %r5
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB1_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw add ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check subtraction of a variable.
define i128 @atomicrmw_sub(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_sub:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB2_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    slgrk %r13, %r4, %r0
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    slbgr %r5, %r1
; CHECK-NEXT:    lgr %r12, %r5
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB2_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw sub ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check AND of a variable.
define i128 @atomicrmw_and(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_and:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB3_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    ngrk %r12, %r5, %r1
; CHECK-NEXT:    ngrk %r13, %r4, %r0
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB3_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw and ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check NAND of a variable.
define i128 @atomicrmw_nand(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_nand:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB4_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    nngrk %r12, %r5, %r1
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    nngrk %r13, %r4, %r0
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB4_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw nand ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check OR of a variable.
define i128 @atomicrmw_or(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_or:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB5_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    ogrk %r12, %r5, %r1
; CHECK-NEXT:    ogrk %r13, %r4, %r0
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB5_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw or ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check XOR of a variable.
define i128 @atomicrmw_xor(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_xor:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB6_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    xgrk %r12, %r5, %r1
; CHECK-NEXT:    xgrk %r13, %r4, %r0
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB6_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw xor ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check signed minimum.
define i128 @atomicrmw_min(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_min:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB7_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    clgr %r4, %r0
; CHECK-NEXT:    lhi %r14, 0
; CHECK-NEXT:    lochile %r14, 1
; CHECK-NEXT:    cgr %r5, %r1
; CHECK-NEXT:    lhi %r13, 0
; CHECK-NEXT:    lochile %r13, 1
; CHECK-NEXT:    locrlh %r14, %r13
; CHECK-NEXT:    chi %r14, 0
; CHECK-NEXT:    selgrlh %r13, %r4, %r0
; CHECK-NEXT:    selgrlh %r12, %r5, %r1
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB7_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw min ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check signed maximum.
define i128 @atomicrmw_max(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_max:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB8_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    clgr %r4, %r0
; CHECK-NEXT:    lhi %r14, 0
; CHECK-NEXT:    lochih %r14, 1
; CHECK-NEXT:    cgr %r5, %r1
; CHECK-NEXT:    lhi %r13, 0
; CHECK-NEXT:    lochih %r13, 1
; CHECK-NEXT:    locrlh %r14, %r13
; CHECK-NEXT:    chi %r14, 0
; CHECK-NEXT:    selgrlh %r13, %r4, %r0
; CHECK-NEXT:    selgrlh %r12, %r5, %r1
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB8_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw max ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check unsigned minimum.
define i128 @atomicrmw_umin(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_umin:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB9_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    clgr %r5, %r1
; CHECK-NEXT:    lhi %r14, 0
; CHECK-NEXT:    lochile %r14, 1
; CHECK-NEXT:    clgr %r4, %r0
; CHECK-NEXT:    lhi %r13, 0
; CHECK-NEXT:    lochile %r13, 1
; CHECK-NEXT:    cgr %r5, %r1
; CHECK-NEXT:    locre %r14, %r13
; CHECK-NEXT:    chi %r14, 0
; CHECK-NEXT:    selgrlh %r13, %r4, %r0
; CHECK-NEXT:    selgrlh %r12, %r5, %r1
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB9_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw umin ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check unsigned maximum.
define i128 @atomicrmw_umax(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_umax:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r4, 8(%r3)
; CHECK-NEXT:    lg %r5, 0(%r3)
; CHECK-NEXT:  .LBB10_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    clgr %r5, %r1
; CHECK-NEXT:    lhi %r14, 0
; CHECK-NEXT:    lochih %r14, 1
; CHECK-NEXT:    clgr %r4, %r0
; CHECK-NEXT:    lhi %r13, 0
; CHECK-NEXT:    lochih %r13, 1
; CHECK-NEXT:    cgr %r5, %r1
; CHECK-NEXT:    locre %r14, %r13
; CHECK-NEXT:    chi %r14, 0
; CHECK-NEXT:    selgrlh %r13, %r4, %r0
; CHECK-NEXT:    selgrlh %r12, %r5, %r1
; CHECK-NEXT:    lgr %r10, %r5
; CHECK-NEXT:    lgr %r11, %r4
; CHECK-NEXT:    cdsg %r10, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r4, %r11
; CHECK-NEXT:    lgr %r5, %r10
; CHECK-NEXT:    jl .LBB10_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r5, 0(%r2)
; CHECK-NEXT:    stg %r4, 8(%r2)
; CHECK-NEXT:    lmg %r10, %r15, 80(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw umax ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check increment with wraparound.
define i128 @atomicrmw_uinc_wrap(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_uinc_wrap:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r8, %r15, 64(%r15)
; CHECK-NEXT:    .cfi_offset %r8, -96
; CHECK-NEXT:    .cfi_offset %r9, -88
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r5, 8(%r3)
; CHECK-NEXT:    lg %r14, 0(%r3)
; CHECK-NEXT:    lghi %r4, 0
; CHECK-NEXT:  .LBB11_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    alghsik %r13, %r5, 1
; CHECK-NEXT:    lgr %r12, %r14
; CHECK-NEXT:    lhi %r11, 0
; CHECK-NEXT:    alcgr %r12, %r4
; CHECK-NEXT:    clgr %r14, %r1
; CHECK-NEXT:    lochihe %r11, 1
; CHECK-NEXT:    clgr %r5, %r0
; CHECK-NEXT:    lhi %r10, 0
; CHECK-NEXT:    lochihe %r10, 1
; CHECK-NEXT:    cgr %r14, %r1
; CHECK-NEXT:    locre %r11, %r10
; CHECK-NEXT:    chi %r11, 0
; CHECK-NEXT:    locghilh %r13, 0
; CHECK-NEXT:    locghilh %r12, 0
; CHECK-NEXT:    lgr %r8, %r14
; CHECK-NEXT:    lgr %r9, %r5
; CHECK-NEXT:    cdsg %r8, %r12, 0(%r3)
; CHECK-NEXT:    lgr %r5, %r9
; CHECK-NEXT:    lgr %r14, %r8
; CHECK-NEXT:    jl .LBB11_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r14, 0(%r2)
; CHECK-NEXT:    stg %r5, 8(%r2)
; CHECK-NEXT:    lmg %r8, %r15, 64(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw uinc_wrap ptr %src, i128 %b seq_cst
  ret i128 %res
}

; Check decrement with wraparound.
define i128 @atomicrmw_udec_wrap(ptr %src, i128 %b) {
; CHECK-LABEL: atomicrmw_udec_wrap:
; CHECK:       # %bb.0:
; CHECK-NEXT:    stmg %r6, %r15, 48(%r15)
; CHECK-NEXT:    .cfi_offset %r6, -112
; CHECK-NEXT:    .cfi_offset %r7, -104
; CHECK-NEXT:    .cfi_offset %r9, -88
; CHECK-NEXT:    .cfi_offset %r10, -80
; CHECK-NEXT:    .cfi_offset %r11, -72
; CHECK-NEXT:    .cfi_offset %r12, -64
; CHECK-NEXT:    .cfi_offset %r13, -56
; CHECK-NEXT:    .cfi_offset %r14, -48
; CHECK-NEXT:    .cfi_offset %r15, -40
; CHECK-NEXT:    lg %r0, 8(%r4)
; CHECK-NEXT:    lg %r1, 0(%r4)
; CHECK-NEXT:    lg %r5, 8(%r3)
; CHECK-NEXT:    lg %r14, 0(%r3)
; CHECK-NEXT:    lghi %r4, -1
; CHECK-NEXT:  .LBB12_1: # %atomicrmw.start
; CHECK-NEXT:    # =>This Inner Loop Header: Depth=1
; CHECK-NEXT:    alghsik %r13, %r5, -1
; CHECK-NEXT:    lgr %r12, %r14
; CHECK-NEXT:    lhi %r10, 0
; CHECK-NEXT:    alcgr %r12, %r4
; CHECK-NEXT:    ogrk %r11, %r5, %r14
; CHECK-NEXT:    lhi %r11, 0
; CHECK-NEXT:    lochie %r11, 1
; CHECK-NEXT:    clgr %r14, %r1
; CHECK-NEXT:    lochih %r10, 1
; CHECK-NEXT:    clgr %r5, %r0
; CHECK-NEXT:    lhi %r9, 0
; CHECK-NEXT:    lochih %r9, 1
; CHECK-NEXT:    cgr %r14, %r1
; CHECK-NEXT:    locre %r10, %r9
; CHECK-NEXT:    or %r11, %r10
; CHECK-NEXT:    selgrl %r11, %r0, %r13
; CHECK-NEXT:    selgrl %r10, %r1, %r12
; CHECK-NEXT:    lgr %r6, %r14
; CHECK-NEXT:    lgr %r7, %r5
; CHECK-NEXT:    cdsg %r6, %r10, 0(%r3)
; CHECK-NEXT:    lgr %r5, %r7
; CHECK-NEXT:    lgr %r14, %r6
; CHECK-NEXT:    jl .LBB12_1
; CHECK-NEXT:  # %bb.2: # %atomicrmw.end
; CHECK-NEXT:    stg %r14, 0(%r2)
; CHECK-NEXT:    stg %r5, 8(%r2)
; CHECK-NEXT:    lmg %r6, %r15, 48(%r15)
; CHECK-NEXT:    br %r14
  %res = atomicrmw udec_wrap ptr %src, i128 %b seq_cst
  ret i128 %res
}
