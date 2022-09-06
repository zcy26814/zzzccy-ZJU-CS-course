; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entry_point:
  %t = alloca i32
  %n = alloca i32
  %c = alloca i32
  %b = alloca i32
  %a = alloca i32
  store i32 0, i32* %a
  store i32 1, i32* %b
  store i32 0, i32* %c
  store i32 0, i32* %n
  store i32 0, i32* %t
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %n)
  br label %cond

cond:                                             ; preds = %loop, %entry_point
  %tmpvar = load i32, i32* %c
  %tmpvar1 = load i32, i32* %n
  %tmpvar2 = load i32, i32* %c
  %tmpvar3 = load i32, i32* %n
  %icmptmp = icmp slt i32 %tmpvar2, %tmpvar3
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %after_loop

loop:                                             ; preds = %cond
  %tmpvar4 = load i32, i32* %b
  store i32 %tmpvar4, i32* %t
  %tmpvar5 = load i32, i32* %a
  %tmpvar6 = load i32, i32* %b
  %tmp_add_i = add i32 %tmpvar5, %tmpvar6
  store i32 %tmp_add_i, i32* %b
  %tmpvar7 = load i32, i32* %t
  store i32 %tmpvar7, i32* %a
  %tmpvar8 = load i32, i32* %c
  %acop_add_i = add i32 %tmpvar8, 1
  store i32 %acop_add_i, i32* %c
  br label %cond

after_loop:                                       ; preds = %cond
  ret i32 0
}
