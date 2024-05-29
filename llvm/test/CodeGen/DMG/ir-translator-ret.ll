; RUN: llc -march=dmg -global-isel -verify-machineinstrs -stop-after=irtranslator < %s | FileCheck %s

; COM: FIXME: EmitInstruction not implemented
; COM: llc -march=dmg -global-isel -verify-machineinstrs < %s | FileCheck --check-prefix=ISEL %s

; COM: FIXME: Cannot identify triple for DMG

; CHECK: name: f
; CHECK: RET
define void @f() {
  ret void
}
