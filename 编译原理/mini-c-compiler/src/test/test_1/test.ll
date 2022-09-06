; ModuleID = 'main'
source_filename = "main"

@a = private global [10001 x i32] zeroinitializer
@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@_Const_String_ = private constant [3 x i8] c"%d\00"
@_Const_String_.1 = private constant [1 x i8] zeroinitializer
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @qsort(i32 %l, i32 %r) {
entry_point:
  %p = alloca i32
  %j = alloca i32
  %i = alloca i32
  %icmptmp = icmp sge i32 %l, %r
  %ifCond = icmp ne i1 %icmptmp, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entry_point
  ret i32 0
  br label %merge

else:                                             ; preds = %entry_point
  br label %merge

merge:                                            ; preds = %else, %then
  store i32 %l, i32* %i
  store i32 %r, i32* %j
  %tmpvar = load i32, i32* %i
  %tmpvar1 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar
  %tmpvar2 = load i32, i32* %tmpvar1
  store i32 %tmpvar2, i32* %p
  br label %cond

cond:                                             ; preds = %merge70, %merge
  %tmpvar3 = load i32, i32* %i
  %tmpvar4 = load i32, i32* %j
  %tmpvar5 = load i32, i32* %i
  %tmpvar6 = load i32, i32* %j
  %icmptmp7 = icmp slt i32 %tmpvar5, %tmpvar6
  %whileCond = icmp ne i1 %icmptmp7, false
  br i1 %whileCond, label %loop, label %after_loop

loop:                                             ; preds = %cond
  br label %cond8

after_loop:                                       ; preds = %cond
  %tmpvar78 = load i32, i32* %i
  %tmp_var79 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar78
  %tmpvar80 = load i32, i32* %p
  store i32 %tmpvar80, i32* %tmp_var79
  %tmpvar81 = load i32, i32* %i
  %tmp_sub_i = sub i32 %tmpvar81, 1
  %call_tmp = call i32 @qsort(i32 %l, i32 %tmp_sub_i)
  %tmpvar82 = load i32, i32* %i
  %tmp_add_i = add i32 %tmpvar82, 1
  %call_tmp83 = call i32 @qsort(i32 %tmp_add_i, i32 %r)
  ret i32 0

cond8:                                            ; preds = %loop9, %loop
  %tmpvar11 = load i32, i32* %i
  %tmpvar12 = load i32, i32* %j
  %tmpvar13 = load i32, i32* %i
  %tmpvar14 = load i32, i32* %j
  %icmptmp15 = icmp slt i32 %tmpvar13, %tmpvar14
  %tmpvar16 = load i32, i32* %j
  %tmpvar17 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar16
  %tmpvar18 = load i32, i32* %tmpvar17
  %tmpvar19 = load i32, i32* %p
  %tmpvar20 = load i32, i32* %j
  %tmpvar21 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar20
  %tmpvar22 = load i32, i32* %tmpvar21
  %tmpvar23 = load i32, i32* %p
  %icmptmp24 = icmp sgt i32 %tmpvar22, %tmpvar23
  %tmp_and = and i1 %icmptmp15, %icmptmp24
  %whileCond25 = icmp ne i1 %tmp_and, false
  br i1 %whileCond25, label %loop9, label %after_loop10

loop9:                                            ; preds = %cond8
  %tmpvar26 = load i32, i32* %j
  %acop_sub_i = sub i32 %tmpvar26, 1
  store i32 %acop_sub_i, i32* %j
  br label %cond8

after_loop10:                                     ; preds = %cond8
  %tmpvar27 = load i32, i32* %i
  %tmpvar28 = load i32, i32* %j
  %tmpvar29 = load i32, i32* %i
  %tmpvar30 = load i32, i32* %j
  %icmptmp31 = icmp slt i32 %tmpvar29, %tmpvar30
  %ifCond32 = icmp ne i1 %icmptmp31, false
  br i1 %ifCond32, label %then33, label %else34

then33:                                           ; preds = %after_loop10
  %tmpvar36 = load i32, i32* %i
  %tmp_var = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar36
  %tmpvar37 = load i32, i32* %j
  %tmpvar38 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar37
  %tmpvar39 = load i32, i32* %tmpvar38
  store i32 %tmpvar39, i32* %tmp_var
  %tmpvar40 = load i32, i32* %i
  %acop_add_i = add i32 %tmpvar40, 1
  store i32 %acop_add_i, i32* %i
  br label %merge35

else34:                                           ; preds = %after_loop10
  br label %merge35

merge35:                                          ; preds = %else34, %then33
  br label %cond41

cond41:                                           ; preds = %loop42, %merge35
  %tmpvar44 = load i32, i32* %i
  %tmpvar45 = load i32, i32* %j
  %tmpvar46 = load i32, i32* %i
  %tmpvar47 = load i32, i32* %j
  %icmptmp48 = icmp slt i32 %tmpvar46, %tmpvar47
  %tmpvar49 = load i32, i32* %i
  %tmpvar50 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar49
  %tmpvar51 = load i32, i32* %tmpvar50
  %tmpvar52 = load i32, i32* %p
  %tmpvar53 = load i32, i32* %i
  %tmpvar54 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar53
  %tmpvar55 = load i32, i32* %tmpvar54
  %tmpvar56 = load i32, i32* %p
  %icmptmp57 = icmp slt i32 %tmpvar55, %tmpvar56
  %tmp_and58 = and i1 %icmptmp48, %icmptmp57
  %whileCond59 = icmp ne i1 %tmp_and58, false
  br i1 %whileCond59, label %loop42, label %after_loop43

loop42:                                           ; preds = %cond41
  %tmpvar60 = load i32, i32* %i
  %acop_add_i61 = add i32 %tmpvar60, 1
  store i32 %acop_add_i61, i32* %i
  br label %cond41

after_loop43:                                     ; preds = %cond41
  %tmpvar62 = load i32, i32* %i
  %tmpvar63 = load i32, i32* %j
  %tmpvar64 = load i32, i32* %i
  %tmpvar65 = load i32, i32* %j
  %icmptmp66 = icmp slt i32 %tmpvar64, %tmpvar65
  %ifCond67 = icmp ne i1 %icmptmp66, false
  br i1 %ifCond67, label %then68, label %else69

then68:                                           ; preds = %after_loop43
  %tmpvar71 = load i32, i32* %j
  %tmp_var72 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar71
  %tmpvar73 = load i32, i32* %i
  %tmpvar74 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar73
  %tmpvar75 = load i32, i32* %tmpvar74
  store i32 %tmpvar75, i32* %tmp_var72
  %tmpvar76 = load i32, i32* %j
  %acop_sub_i77 = sub i32 %tmpvar76, 1
  store i32 %acop_sub_i77, i32* %j
  br label %merge70

else69:                                           ; preds = %after_loop43
  br label %merge70

merge70:                                          ; preds = %else69, %then68
  br label %cond
}

define i32 @main() {
entry_point:
  %i = alloca i32
  %n = alloca i32
  store i32 0, i32* %n
  store i32 0, i32* %i
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %n)
  br label %cond

cond:                                             ; preds = %loop, %entry_point
  %tmpvar = load i32, i32* %i
  %tmpvar1 = load i32, i32* %n
  %tmpvar2 = load i32, i32* %i
  %tmpvar3 = load i32, i32* %n
  %icmptmp = icmp slt i32 %tmpvar2, %tmpvar3
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %after_loop

loop:                                             ; preds = %cond
  %tmpvar4 = load i32, i32* %i
  %tmp_var = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar4
  %scanf5 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %tmp_var)
  %tmpvar6 = load i32, i32* %i
  %acop_add_i = add i32 %tmpvar6, 1
  store i32 %acop_add_i, i32* %i
  br label %cond

after_loop:                                       ; preds = %cond
  %tmpvar7 = load i32, i32* %n
  %tmp_sub_i = sub i32 %tmpvar7, 1
  %call_tmp = call i32 @qsort(i32 0, i32 %tmp_sub_i)
  store i32 0, i32* %i
  br label %cond8

cond8:                                            ; preds = %loop9, %after_loop
  %tmpvar11 = load i32, i32* %i
  %tmpvar12 = load i32, i32* %n
  %tmpvar13 = load i32, i32* %i
  %tmpvar14 = load i32, i32* %n
  %icmptmp15 = icmp slt i32 %tmpvar13, %tmpvar14
  %whileCond16 = icmp ne i1 %icmptmp15, false
  br i1 %whileCond16, label %loop9, label %after_loop10

loop9:                                            ; preds = %cond8
  %tmpvar17 = load i32, i32* %i
  %tmpvar18 = getelementptr inbounds [10001 x i32], [10001 x i32]* @a, i32 0, i32 %tmpvar17
  %tmpvar19 = load i32, i32* %tmpvar18
  %print_str = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_, i32 0, i32 0), i32 %tmpvar19)
  %print_str20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.1, i32 0, i32 0))
  %println_token = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @2, i32 0, i32 0))
  %tmpvar21 = load i32, i32* %i
  %acop_add_i22 = add i32 %tmpvar21, 1
  store i32 %acop_add_i22, i32* %i
  br label %cond8

after_loop10:                                     ; preds = %cond8
  ret i32 0
}
