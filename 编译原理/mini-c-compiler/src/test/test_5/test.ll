; ModuleID = 'main'
source_filename = "main"

@_Const_String_ = private constant [4 x i8] c"YES\00"
@0 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.1 = private constant [3 x i8] c"NO\00"
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entry_point:
  %b = alloca i32
  %a = alloca i32
  store i32 3, i32* %a
  store i32 5, i32* %b
  %tmpvar = load i32, i32* %a
  %tmp_rem_f = urem i32 %tmpvar, 2
  %tmpvar1 = load i32, i32* %b
  %tmp_rem_f2 = urem i32 %tmpvar1, 2
  %tmpvar3 = load i32, i32* %a
  %tmp_rem_f4 = urem i32 %tmpvar3, 2
  %tmpvar5 = load i32, i32* %b
  %tmp_rem_f6 = urem i32 %tmpvar5, 2
  %icmptmp = icmp eq i32 %tmp_rem_f4, %tmp_rem_f6
  %ifCond = icmp ne i1 %icmptmp, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entry_point
  %print_str = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @_Const_String_, i32 0, i32 0))
  %println_token = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @0, i32 0, i32 0))
  br label %merge

else:                                             ; preds = %entry_point
  %print_str7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_.1, i32 0, i32 0))
  %println_token8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  br label %merge

merge:                                            ; preds = %else, %then
  ret i32 0
}
