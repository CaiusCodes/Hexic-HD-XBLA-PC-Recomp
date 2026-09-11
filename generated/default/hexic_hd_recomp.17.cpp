#include "hexic_hd_init.h"

DEFINE_REX_FUNC(sub_922463A0) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b474
	ctx.lr = 0x922463A8;
	__savegprlr_27(ctx, base);
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lwz r11,124(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 124);
	// li r27,0
	ctx.r27.s64 = 0;
	// mr r30,r4
	ctx.r30.u64 = ctx.r4.u64;
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// lis r11,-28156
	ctx.r11.s64 = -1845231616;
	// mr r31,r5
	ctx.r31.u64 = ctx.r5.u64;
	// mr r29,r6
	ctx.r29.u64 = ctx.r6.u64;
	// mr r8,r27
	ctx.r8.u64 = ctx.r27.u64;
	// addi r28,r11,948
	ctx.r28.s64 = ctx.r11.s64 + 948;
	// ble cr6,0x922464e0
	if (!ctx.cr6.gt) goto loc_922464E0;
	// lbz r11,28(r3)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r3.u32 + 28);
	// cmplwi cr6,r11,2
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 2, ctx.xer);
	// bne cr6,0x92246450
	if (!ctx.cr6.eq) goto loc_92246450;
	// mr r7,r27
	ctx.r7.u64 = ctx.r27.u64;
	// mr r9,r27
	ctx.r9.u64 = ctx.r27.u64;
	// addi r10,r3,140
	ctx.r10.s64 = ctx.r3.s64 + 140;
	// li r11,7
	ctx.r11.s64 = 7;
loc_922463F0:
	// lhz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// add r9,r8,r9
	ctx.r9.u64 = ctx.r8.u64 + ctx.r9.u64;
	// bne 0x922463f0
	if (!ctx.cr0.eq) goto loc_922463F0;
	// addi r10,r3,168
	ctx.r10.s64 = ctx.r3.s64 + 168;
	// li r11,121
	ctx.r11.s64 = 121;
loc_9224640C:
	// lhz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// add r7,r8,r7
	ctx.r7.u64 = ctx.r8.u64 + ctx.r7.u64;
	// bne 0x9224640c
	if (!ctx.cr0.eq) goto loc_9224640C;
	// addi r10,r3,652
	ctx.r10.s64 = ctx.r3.s64 + 652;
	// li r11,128
	ctx.r11.s64 = 128;
loc_92246428:
	// lhz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// add r9,r8,r9
	ctx.r9.u64 = ctx.r8.u64 + ctx.r9.u64;
	// bne 0x92246428
	if (!ctx.cr0.eq) goto loc_92246428;
	// rlwinm r11,r7,30,2,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r7.u32 | (ctx.r7.u64 << 32), 30) & 0x3FFFFFFF;
	// subfc r11,r9,r11
	ctx.xer.ca = ctx.r11.u32 >= ctx.r9.u32;
	ctx.r11.u64 = ctx.r11.u64 - ctx.r9.u64;
	// subfe r11,r11,r11
	temp.u8 = (~ctx.r11.u32 + ctx.r11.u32 < ~ctx.r11.u32) | (~ctx.r11.u32 + ctx.r11.u32 + ctx.xer.ca < ctx.xer.ca);
	ctx.r11.u64 = ~ctx.r11.u64 + ctx.r11.u64 + ctx.xer.ca;
	ctx.xer.ca = temp.u8;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stb r11,28(r3)
	REX_STORE_U8(ctx.r3.u32 + 28, ctx.r11.u8);
loc_92246450:
	// addi r4,r3,2832
	ctx.r4.s64 = ctx.r3.s64 + 2832;
	// bl 0x92246030
	ctx.lr = 0x92246458;
	sub_92246030(ctx, base);
	// addi r4,r3,2844
	ctx.r4.s64 = ctx.r3.s64 + 2844;
	// bl 0x92246030
	ctx.lr = 0x92246460;
	sub_92246030(ctx, base);
	// addi r4,r3,140
	ctx.r4.s64 = ctx.r3.s64 + 140;
	// lwz r5,2836(r3)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r3.u32 + 2836);
	// bl 0x921c1768
	ctx.lr = 0x9224646C;
	sub_921C1768(ctx, base);
	// addi r4,r3,2432
	ctx.r4.s64 = ctx.r3.s64 + 2432;
	// lwz r5,2848(r3)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r3.u32 + 2848);
	// bl 0x921c1768
	ctx.lr = 0x92246478;
	sub_921C1768(ctx, base);
	// addi r4,r3,2856
	ctx.r4.s64 = ctx.r3.s64 + 2856;
	// bl 0x92246030
	ctx.lr = 0x92246480;
	sub_92246030(ctx, base);
	// li r11,18
	ctx.r11.s64 = 18;
loc_92246484:
	// lbzx r10,r11,r28
	ctx.r10.u64 = REX_LOAD_U8(ctx.r11.u32 + ctx.r28.u32);
	// rotlwi r10,r10,2
	ctx.r10.u64 = __builtin_rotateleft32(ctx.r10.u32, 2);
	// add r10,r10,r3
	ctx.r10.u64 = ctx.r10.u64 + ctx.r3.u64;
	// lhz r10,2678(r10)
	ctx.r10.u64 = REX_LOAD_U16(ctx.r10.u32 + 2678);
	// cmplwi r10,0
	ctx.cr0.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// bne 0x922464a8
	if (!ctx.cr0.eq) goto loc_922464A8;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// cmpwi cr6,r11,3
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 3, ctx.xer);
	// bge cr6,0x92246484
	if (!ctx.cr6.lt) goto loc_92246484;
loc_922464A8:
	// mulli r10,r11,3
	ctx.r10.s64 = static_cast<int64_t>(ctx.r11.u64 * static_cast<uint64_t>(3));
	// lwz r9,5796(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 5796);
	// mr r8,r11
	ctx.r8.u64 = ctx.r11.u64;
	// addi r9,r9,10
	ctx.r9.s64 = ctx.r9.s64 + 10;
	// lwz r11,5792(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 5792);
	// add r11,r10,r11
	ctx.r11.u64 = ctx.r10.u64 + ctx.r11.u64;
	// rlwinm r9,r9,29,3,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 29) & 0x1FFFFFFF;
	// addi r11,r11,17
	ctx.r11.s64 = ctx.r11.s64 + 17;
	// addi r10,r11,10
	ctx.r10.s64 = ctx.r11.s64 + 10;
	// rlwinm r10,r10,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 29) & 0x1FFFFFFF;
	// stw r11,5792(r3)
	REX_STORE_U32(ctx.r3.u32 + 5792, ctx.r11.u32);
	// cmplw cr6,r9,r10
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r10.u32, ctx.xer);
	// bgt cr6,0x922464e8
	if (ctx.cr6.gt) goto loc_922464E8;
	// b 0x922464e4
	goto loc_922464E4;
loc_922464E0:
	// addi r9,r31,5
	ctx.r9.s64 = ctx.r31.s64 + 5;
loc_922464E4:
	// mr r10,r9
	ctx.r10.u64 = ctx.r9.u64;
loc_922464E8:
	// addi r11,r31,4
	ctx.r11.s64 = ctx.r31.s64 + 4;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bgt cr6,0x92246510
	if (ctx.cr6.gt) goto loc_92246510;
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x92246510
	if (ctx.cr6.eq) goto loc_92246510;
	// mr r6,r29
	ctx.r6.u64 = ctx.r29.u64;
	// mr r5,r31
	ctx.r5.u64 = ctx.r31.u64;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// bl 0x92246310
	ctx.lr = 0x9224650C;
	sub_92246310(ctx, base);
	// b 0x9224665c
	goto loc_9224665C;
loc_92246510:
	// cmplw cr6,r9,r10
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r10.u32, ctx.xer);
	// lwz r10,5812(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 5812);
	// bne cr6,0x922465b0
	if (!ctx.cr6.eq) goto loc_922465B0;
	// cmpwi cr6,r10,13
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 13, ctx.xer);
	// addi r11,r29,2
	ctx.r11.s64 = ctx.r29.s64 + 2;
	// ble cr6,0x9224658c
	if (!ctx.cr6.gt) goto loc_9224658C;
	// slw r10,r11,r10
	ctx.r10.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r10.u8 & 0x3F));
	// lhz r9,5808(r3)
	ctx.r9.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// clrlwi r7,r11,16
	ctx.r7.u64 = ctx.r11.u32 & 0xFFFF;
	// lwz r8,20(r3)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// or r11,r10,r9
	ctx.r11.u64 = ctx.r10.u64 | ctx.r9.u64;
	// lwz r10,8(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// clrlwi r11,r11,16
	ctx.r11.u64 = ctx.r11.u32 & 0xFFFF;
	// sth r11,5808(r3)
	REX_STORE_U16(ctx.r3.u32 + 5808, ctx.r11.u16);
	// stbx r11,r10,r8
	REX_STORE_U8(ctx.r10.u32 + ctx.r8.u32, ctx.r11.u8);
	// lwz r11,20(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lbz r10,5808(r3)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r3.u32 + 5808);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// lwz r9,8(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// stw r11,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r11.u32);
	// stbx r10,r9,r11
	REX_STORE_U8(ctx.r9.u32 + ctx.r11.u32, ctx.r10.u8);
	// lwz r10,20(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lwz r11,5812(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 5812);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// stw r10,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r10.u32);
	// addi r10,r11,-13
	ctx.r10.s64 = ctx.r11.s64 + -13;
	// subfic r11,r11,16
	ctx.xer.ca = ctx.r11.u32 <= 16;
	ctx.r11.u64 = static_cast<uint64_t>(16) - ctx.r11.u64;
	// clrlwi r11,r11,16
	ctx.r11.u64 = ctx.r11.u32 & 0xFFFF;
	// stw r10,5812(r3)
	REX_STORE_U32(ctx.r3.u32 + 5812, ctx.r10.u32);
	// srw r11,r7,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r7.u32 >> (ctx.r11.u8 & 0x3F));
	// b 0x922465a0
	goto loc_922465A0;
loc_9224658C:
	// addi r9,r10,3
	ctx.r9.s64 = ctx.r10.s64 + 3;
	// slw r11,r11,r10
	ctx.r11.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r10.u8 & 0x3F));
	// lhz r10,5808(r3)
	ctx.r10.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// or r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 | ctx.r10.u64;
	// stw r9,5812(r3)
	REX_STORE_U32(ctx.r3.u32 + 5812, ctx.r9.u32);
loc_922465A0:
	// sth r11,5808(r3)
	REX_STORE_U16(ctx.r3.u32 + 5808, ctx.r11.u16);
	// addi r5,r28,1372
	ctx.r5.s64 = ctx.r28.s64 + 1372;
	// addi r4,r28,220
	ctx.r4.s64 = ctx.r28.s64 + 220;
	// b 0x92246658
	goto loc_92246658;
loc_922465B0:
	// cmpwi cr6,r10,13
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 13, ctx.xer);
	// addi r11,r29,4
	ctx.r11.s64 = ctx.r29.s64 + 4;
	// ble cr6,0x92246620
	if (!ctx.cr6.gt) goto loc_92246620;
	// slw r10,r11,r10
	ctx.r10.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r10.u8 & 0x3F));
	// lhz r9,5808(r3)
	ctx.r9.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// clrlwi r6,r11,16
	ctx.r6.u64 = ctx.r11.u32 & 0xFFFF;
	// lwz r7,20(r3)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// or r11,r10,r9
	ctx.r11.u64 = ctx.r10.u64 | ctx.r9.u64;
	// lwz r10,8(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// clrlwi r11,r11,16
	ctx.r11.u64 = ctx.r11.u32 & 0xFFFF;
	// sth r11,5808(r3)
	REX_STORE_U16(ctx.r3.u32 + 5808, ctx.r11.u16);
	// stbx r11,r10,r7
	REX_STORE_U8(ctx.r10.u32 + ctx.r7.u32, ctx.r11.u8);
	// lwz r11,20(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lbz r10,5808(r3)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r3.u32 + 5808);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// lwz r9,8(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// stw r11,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r11.u32);
	// stbx r10,r9,r11
	REX_STORE_U8(ctx.r9.u32 + ctx.r11.u32, ctx.r10.u8);
	// lwz r10,20(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lwz r11,5812(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 5812);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// stw r10,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r10.u32);
	// addi r10,r11,-13
	ctx.r10.s64 = ctx.r11.s64 + -13;
	// subfic r11,r11,16
	ctx.xer.ca = ctx.r11.u32 <= 16;
	ctx.r11.u64 = static_cast<uint64_t>(16) - ctx.r11.u64;
	// clrlwi r11,r11,16
	ctx.r11.u64 = ctx.r11.u32 & 0xFFFF;
	// stw r10,5812(r3)
	REX_STORE_U32(ctx.r3.u32 + 5812, ctx.r10.u32);
	// srw r11,r6,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r6.u32 >> (ctx.r11.u8 & 0x3F));
	// b 0x92246634
	goto loc_92246634;
loc_92246620:
	// addi r9,r10,3
	ctx.r9.s64 = ctx.r10.s64 + 3;
	// slw r11,r11,r10
	ctx.r11.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r10.u8 & 0x3F));
	// lhz r10,5808(r3)
	ctx.r10.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// or r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 | ctx.r10.u64;
	// stw r9,5812(r3)
	REX_STORE_U32(ctx.r3.u32 + 5812, ctx.r9.u32);
loc_92246634:
	// sth r11,5808(r3)
	REX_STORE_U16(ctx.r3.u32 + 5808, ctx.r11.u16);
	// addi r6,r8,1
	ctx.r6.s64 = ctx.r8.s64 + 1;
	// lwz r10,2848(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 2848);
	// lwz r11,2836(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 2836);
	// addi r5,r10,1
	ctx.r5.s64 = ctx.r10.s64 + 1;
	// addi r4,r11,1
	ctx.r4.s64 = ctx.r11.s64 + 1;
	// bl 0x92245938
	ctx.lr = 0x92246650;
	sub_92245938(ctx, base);
	// addi r5,r3,2432
	ctx.r5.s64 = ctx.r3.s64 + 2432;
	// addi r4,r3,140
	ctx.r4.s64 = ctx.r3.s64 + 140;
loc_92246658:
	// bl 0x92245bd8
	ctx.lr = 0x9224665C;
	sub_92245BD8(ctx, base);
loc_9224665C:
	// addi r10,r3,140
	ctx.r10.s64 = ctx.r3.s64 + 140;
	// li r11,286
	ctx.r11.s64 = 286;
loc_92246664:
	// sth r27,0(r10)
	REX_STORE_U16(ctx.r10.u32 + 0, ctx.r27.u16);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// bne 0x92246664
	if (!ctx.cr0.eq) goto loc_92246664;
	// addi r10,r3,2432
	ctx.r10.s64 = ctx.r3.s64 + 2432;
	// li r11,30
	ctx.r11.s64 = 30;
loc_9224667C:
	// sth r27,0(r10)
	REX_STORE_U16(ctx.r10.u32 + 0, ctx.r27.u16);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// bne 0x9224667c
	if (!ctx.cr0.eq) goto loc_9224667C;
	// addi r10,r3,2676
	ctx.r10.s64 = ctx.r3.s64 + 2676;
	// li r11,19
	ctx.r11.s64 = 19;
loc_92246694:
	// sth r27,0(r10)
	REX_STORE_U16(ctx.r10.u32 + 0, ctx.r27.u16);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// bne 0x92246694
	if (!ctx.cr0.eq) goto loc_92246694;
	// li r11,1
	ctx.r11.s64 = 1;
	// stw r27,5796(r3)
	REX_STORE_U32(ctx.r3.u32 + 5796, ctx.r27.u32);
	// cmpwi cr6,r29,0
	ctx.cr6.compare<int32_t>(ctx.r29.s32, 0, ctx.xer);
	// stw r27,5792(r3)
	REX_STORE_U32(ctx.r3.u32 + 5792, ctx.r27.u32);
	// stw r27,5800(r3)
	REX_STORE_U32(ctx.r3.u32 + 5800, ctx.r27.u32);
	// stw r27,5784(r3)
	REX_STORE_U32(ctx.r3.u32 + 5784, ctx.r27.u32);
	// sth r11,1164(r3)
	REX_STORE_U16(ctx.r3.u32 + 1164, ctx.r11.u16);
	// beq cr6,0x92246728
	if (ctx.cr6.eq) goto loc_92246728;
	// lwz r11,5812(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 5812);
	// cmpwi cr6,r11,8
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 8, ctx.xer);
	// ble cr6,0x922466fc
	if (!ctx.cr6.gt) goto loc_922466FC;
	// lwz r10,20(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lhz r11,5808(r3)
	ctx.r11.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// lwz r9,8(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// stbx r11,r9,r10
	REX_STORE_U8(ctx.r9.u32 + ctx.r10.u32, ctx.r11.u8);
	// lwz r11,20(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// lwz r10,8(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// lbz r9,5808(r3)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r3.u32 + 5808);
	// stw r11,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r11.u32);
	// stbx r9,r10,r11
	REX_STORE_U8(ctx.r10.u32 + ctx.r11.u32, ctx.r9.u8);
	// b 0x92246714
	goto loc_92246714;
loc_922466FC:
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// ble cr6,0x92246720
	if (!ctx.cr6.gt) goto loc_92246720;
	// lhz r11,5808(r3)
	ctx.r11.u64 = REX_LOAD_U16(ctx.r3.u32 + 5808);
	// lwz r10,8(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 8);
	// lwz r9,20(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// stbx r11,r10,r9
	REX_STORE_U8(ctx.r10.u32 + ctx.r9.u32, ctx.r11.u8);
loc_92246714:
	// lwz r11,20(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 20);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,20(r3)
	REX_STORE_U32(ctx.r3.u32 + 20, ctx.r11.u32);
loc_92246720:
	// sth r27,5808(r3)
	REX_STORE_U16(ctx.r3.u32 + 5808, ctx.r27.u16);
	// stw r27,5812(r3)
	REX_STORE_U32(ctx.r3.u32 + 5812, ctx.r27.u32);
loc_92246728:
	// addi r1,r1,128
	ctx.r1.s64 = ctx.r1.s64 + 128;
	// b 0x9205b4c4
	__restgprlr_27(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92246730) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b47c
	ctx.lr = 0x92246738;
	__savegprlr_29(ctx, base);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r30,r5
	ctx.r30.u64 = ctx.r5.u64;
	// mullw r29,r4,r30
	ctx.r29.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r30.s32);
	// lis r4,9345
	ctx.r4.s64 = 612433920;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x921efbf8
	ctx.lr = 0x92246750;
	sub_921EFBF8(ctx, base);
	// mr. r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// beq 0x92246780
	if (ctx.cr0.eq) goto loc_92246780;
	// divwu r11,r31,r30
	ctx.r11.u64 = uint32_t(ctx.r30.u32 ? ctx.r31.u32 / ctx.r30.u32 : 0);
	// twllei r30,0
	if (ctx.r30.s32 == 0 || ctx.r30.u32 < 0u) ppc_trap(ctx, base, 0);
	// mullw r11,r11,r30
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r30.s32);
	// subf. r11,r11,r31
	ctx.r11.u64 = ctx.r31.u64 - ctx.r11.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x92246770
	if (ctx.cr0.eq) goto loc_92246770;
	// twi 31,r0,22
	ppc_trap(ctx, base, 22);
loc_92246770:
	// mr r5,r29
	ctx.r5.u64 = ctx.r29.u64;
	// li r4,0
	ctx.r4.s64 = 0;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9205cd70
	ctx.lr = 0x92246780;
	sub_9205CD70(ctx, base);
loc_92246780:
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// b 0x9205b4cc
	__restgprlr_29(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92246790) {
	REX_FUNC_PROLOGUE();
	// mr r3,r4
	ctx.r3.u64 = ctx.r4.u64;
	// lis r4,9345
	ctx.r4.s64 = 612433920;
	// b 0x921efc90
	sub_921EFC90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_922467A0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b478
	ctx.lr = 0x922467A8;
	__savegprlr_28(ctx, base);
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r28,r4
	ctx.r28.u64 = ctx.r4.u64;
	// mr r29,r5
	ctx.r29.u64 = ctx.r5.u64;
	// li r5,64
	ctx.r5.s64 = 64;
	// li r4,1
	ctx.r4.s64 = 1;
	// lwz r11,32(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x922467D0;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr. r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// bne 0x922467e0
	if (!ctx.cr0.eq) goto loc_922467E0;
loc_922467D8:
	// li r3,0
	ctx.r3.s64 = 0;
	// b 0x92246880
	goto loc_92246880;
loc_922467E0:
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// li r5,1440
	ctx.r5.s64 = 1440;
	// lwz r11,32(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// li r4,8
	ctx.r4.s64 = 8;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x922467F8;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// stw r3,36(r31)
	REX_STORE_U32(ctx.r31.u32 + 36, ctx.r3.u32);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// bne 0x9224681c
	if (!ctx.cr0.eq) goto loc_9224681C;
loc_92246808:
	// lwz r11,36(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92246818;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// b 0x922467d8
	goto loc_922467D8;
loc_9224681C:
	// lwz r11,32(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// mr r5,r29
	ctx.r5.u64 = ctx.r29.u64;
	// li r4,1
	ctx.r4.s64 = 1;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92246830;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// stw r3,40(r31)
	REX_STORE_U32(ctx.r31.u32 + 40, ctx.r3.u32);
	// bne 0x92246858
	if (!ctx.cr0.eq) goto loc_92246858;
	// lwz r4,36(r31)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r11,36(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92246850;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// b 0x92246808
	goto loc_92246808;
loc_92246858:
	// add r11,r3,r29
	ctx.r11.u64 = ctx.r3.u64 + ctx.r29.u64;
	// stw r28,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r28.u32);
	// li r10,0
	ctx.r10.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// stw r11,44(r31)
	REX_STORE_U32(ctx.r31.u32 + 44, ctx.r11.u32);
	// stw r10,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r10.u32);
	// bl 0x921c29e8
	ctx.lr = 0x9224687C;
	sub_921C29E8(ctx, base);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
loc_92246880:
	// addi r1,r1,128
	ctx.r1.s64 = ctx.r1.s64 + 128;
	// b 0x9205b4c8
	__restgprlr_28(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92246888) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b448
	ctx.lr = 0x92246890;
	__savegprlr_16(ctx, base);
	// stwu r1,-272(r1)
	ea = -272 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r30,r4
	ctx.r30.u64 = ctx.r4.u64;
	// mr r22,r5
	ctx.r22.u64 = ctx.r5.u64;
	// lwz r26,52(r31)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r11,48(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// lwz r29,0(r30)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwz r24,4(r30)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r30.u32 + 4);
	// cmplw cr6,r26,r11
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r11.u32, ctx.xer);
	// lwz r27,32(r31)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r31.u32 + 32);
	// lwz r28,28(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// bge cr6,0x922468cc
	if (!ctx.cr6.lt) goto loc_922468CC;
	// subf r11,r26,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r26.u64;
	// addi r23,r11,-1
	ctx.r23.s64 = ctx.r11.s64 + -1;
	// b 0x922468d4
	goto loc_922468D4;
loc_922468CC:
	// lwz r11,44(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// subf r23,r26,r11
	ctx.r23.u64 = ctx.r11.u64 - ctx.r26.u64;
loc_922468D4:
	// lwz r10,0(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// cmplwi cr6,r10,9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 9, ctx.xer);
	// bgt cr6,0x92246fc8
	if (ctx.cr6.gt) goto loc_92246FC8;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r21,0
	ctx.r21.s64 = 0;
	// addi r19,r11,-1712
	ctx.r19.s64 = ctx.r11.s64 + -1712;
	// lis r11,-28156
	ctx.r11.s64 = -1845231616;
	// li r18,6
	ctx.r18.s64 = 6;
	// addi r17,r11,3448
	ctx.r17.s64 = ctx.r11.s64 + 3448;
	// li r16,7
	ctx.r16.s64 = 7;
	// li r20,9
	ctx.r20.s64 = 9;
loc_92246900:
	// lis r12,-28156
	ctx.r12.s64 = -1845231616;
	// addi r12,r12,3528
	ctx.r12.s64 = ctx.r12.s64 + 3528;
	// rlwinm r0,r10,1,0,30
	ctx.r0.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0xFFFFFFFE;
	// lhzx r0,r12,r0
	ctx.r0.u64 = REX_LOAD_U16(ctx.r12.u32 + ctx.r0.u32);
	// lis r12,-28124
	ctx.r12.s64 = -1843134464;
	// addi r12,r12,26920
	ctx.r12.s64 = ctx.r12.s64 + 26920;
	// add r12,r12,r0
	ctx.r12.u64 = ctx.r12.u64 + ctx.r0.u64;
	// mtctr r12
	ctx.ctr.u64 = ctx.r12.u64;
	// nop 
	// bctr 
	switch (ctx.r10.u32) {
	case 0:
		goto loc_9224694C;
	case 1:
		goto loc_92246A44;
	case 2:
		goto loc_92246A98;
	case 3:
		goto loc_92246BD8;
	case 4:
		goto loc_92246C9C;
	case 5:
		goto loc_92246E7C;
	case 6:
		goto loc_92246F24;
	case 7:
		goto loc_9224709C;
	case 8:
		goto loc_922470CC;
	case 9:
		goto loc_92247034;
	default:
		__builtin_trap(); // Switch case out of range
	}
loc_92246928:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r11,r11,r28
	ctx.r11.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r11,r27
	ctx.r27.u64 = ctx.r11.u64 | ctx.r27.u64;
loc_9224694C:
	// cmplwi cr6,r28,3
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 3, ctx.xer);
	// blt cr6,0x92246928
	if (ctx.cr6.lt) goto loc_92246928;
	// clrlwi r11,r27,29
	ctx.r11.u64 = ctx.r27.u32 & 0x7;
	// rlwinm r10,r11,31,1,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 31) & 0x7FFFFFFF;
	// clrlwi r11,r11,31
	ctx.r11.u64 = ctx.r11.u32 & 0x1;
	// cmplwi cr6,r10,1
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 1, ctx.xer);
	// stw r11,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r11.u32);
	// blt cr6,0x92246a00
	if (ctx.cr6.lt) goto loc_92246A00;
	// beq cr6,0x922469b4
	if (ctx.cr6.eq) goto loc_922469B4;
	// cmplwi cr6,r10,3
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 3, ctx.xer);
	// blt cr6,0x922469a4
	if (ctx.cr6.lt) goto loc_922469A4;
	// bne cr6,0x92246fbc
	if (!ctx.cr6.eq) goto loc_92246FBC;
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// stw r20,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r20.u32);
	// rlwinm r10,r27,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 29) & 0x1FFFFFFF;
	// addi r11,r11,19908
	ctx.r11.s64 = ctx.r11.s64 + 19908;
	// addi r9,r28,-3
	ctx.r9.s64 = ctx.r28.s64 + -3;
	// li r5,-3
	ctx.r5.s64 = -3;
	// stw r11,24(r30)
	REX_STORE_U32(ctx.r30.u32 + 24, ctx.r11.u32);
	// stw r10,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r10.u32);
	// stw r9,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r9.u32);
	// b 0x92246fd4
	goto loc_92246FD4;
loc_922469A4:
	// rlwinm r27,r27,29,3,31
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 29) & 0x1FFFFFFF;
	// addi r28,r28,-3
	ctx.r28.s64 = ctx.r28.s64 + -3;
	// li r11,3
	ctx.r11.s64 = 3;
	// b 0x92246a90
	goto loc_92246A90;
loc_922469B4:
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// addi r6,r1,104
	ctx.r6.s64 = ctx.r1.s64 + 104;
	// addi r5,r1,108
	ctx.r5.s64 = ctx.r1.s64 + 108;
	// addi r4,r1,112
	ctx.r4.s64 = ctx.r1.s64 + 112;
	// addi r3,r1,116
	ctx.r3.s64 = ctx.r1.s64 + 116;
	// bl 0x922495b8
	ctx.lr = 0x922469CC;
	sub_922495B8(ctx, base);
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// lwz r6,104(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + 104);
	// lwz r5,108(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// lwz r4,112(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
	// lwz r3,116(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 116);
	// bl 0x921c32f8
	ctx.lr = 0x922469E4;
	sub_921C32F8(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// stw r3,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r3.u32);
	// beq 0x9224701c
	if (ctx.cr0.eq) goto loc_9224701C;
	// rlwinm r27,r27,29,3,31
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 29) & 0x1FFFFFFF;
	// stw r18,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r18.u32);
	// addi r28,r28,-3
	ctx.r28.s64 = ctx.r28.s64 + -3;
	// b 0x92246fbc
	goto loc_92246FBC;
loc_92246A00:
	// li r10,1
	ctx.r10.s64 = 1;
	// addi r11,r28,-3
	ctx.r11.s64 = ctx.r28.s64 + -3;
	// rlwinm r9,r27,29,3,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 29) & 0x1FFFFFFF;
	// stw r10,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r10.u32);
	// clrlwi r10,r11,29
	ctx.r10.u64 = ctx.r11.u32 & 0x7;
	// subf r28,r10,r11
	ctx.r28.u64 = ctx.r11.u64 - ctx.r10.u64;
	// srw r27,r9,r10
	ctx.r27.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r9.u32 >> (ctx.r10.u8 & 0x3F));
	// b 0x92246fbc
	goto loc_92246FBC;
loc_92246A20:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r11,r11,r28
	ctx.r11.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r11,r27
	ctx.r27.u64 = ctx.r11.u64 | ctx.r27.u64;
loc_92246A44:
	// cmplwi cr6,r28,32
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 32, ctx.xer);
	// blt cr6,0x92246a20
	if (ctx.cr6.lt) goto loc_92246A20;
	// not r10,r27
	ctx.r10.u64 = ~ctx.r27.u64;
	// clrlwi r11,r27,16
	ctx.r11.u64 = ctx.r27.u32 & 0xFFFF;
	// rlwinm r10,r10,16,16,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 16) & 0xFFFF;
	// cmplw cr6,r10,r11
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r11.u32, ctx.xer);
	// bne cr6,0x92247024
	if (!ctx.cr6.eq) goto loc_92247024;
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// rotlwi r11,r11,0
	ctx.r11.u64 = __builtin_rotateleft32(ctx.r11.u32, 0);
	// mr r28,r21
	ctx.r28.u64 = ctx.r21.u64;
	// mr r27,r21
	ctx.r27.u64 = ctx.r21.u64;
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x92246a80
	if (ctx.cr6.eq) goto loc_92246A80;
	// li r11,2
	ctx.r11.s64 = 2;
	// b 0x92246a90
	goto loc_92246A90;
loc_92246A80:
	// lwz r11,24(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 24);
	// subfic r11,r11,0
	ctx.xer.ca = ctx.r11.u32 <= 0;
	ctx.r11.u64 = static_cast<uint64_t>(0) - ctx.r11.u64;
	// subfe r11,r11,r11
	temp.u8 = (~ctx.r11.u32 + ctx.r11.u32 < ~ctx.r11.u32) | (~ctx.r11.u32 + ctx.r11.u32 + ctx.xer.ca < ctx.xer.ca);
	ctx.r11.u64 = ~ctx.r11.u64 + ctx.r11.u64 + ctx.xer.ca;
	ctx.xer.ca = temp.u8;
	// clrlwi r11,r11,29
	ctx.r11.u64 = ctx.r11.u32 & 0x7;
loc_92246A90:
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
	// b 0x92246fbc
	goto loc_92246FBC;
loc_92246A98:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// cmplwi cr6,r23,0
	ctx.cr6.compare<uint32_t>(ctx.r23.u32, 0, ctx.xer);
	// bne cr6,0x92246b60
	if (!ctx.cr6.eq) goto loc_92246B60;
	// lwz r9,44(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// cmplw cr6,r26,r9
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r9.u32, ctx.xer);
	// bne cr6,0x92246ae8
	if (!ctx.cr6.eq) goto loc_92246AE8;
	// lwz r11,48(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// lwz r10,40(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// beq cr6,0x92246ae8
	if (ctx.cr6.eq) goto loc_92246AE8;
	// mr r26,r10
	ctx.r26.u64 = ctx.r10.u64;
	// cmplw cr6,r26,r11
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r11.u32, ctx.xer);
	// bge cr6,0x92246adc
	if (!ctx.cr6.lt) goto loc_92246ADC;
	// subf r11,r26,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r26.u64;
	// addi r23,r11,-1
	ctx.r23.s64 = ctx.r11.s64 + -1;
	// b 0x92246ae0
	goto loc_92246AE0;
loc_92246ADC:
	// subf r23,r26,r9
	ctx.r23.u64 = ctx.r9.u64 - ctx.r26.u64;
loc_92246AE0:
	// cmplwi cr6,r23,0
	ctx.cr6.compare<uint32_t>(ctx.r23.u32, 0, ctx.xer);
	// bne cr6,0x92246b60
	if (!ctx.cr6.eq) goto loc_92246B60;
loc_92246AE8:
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// stw r26,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r26.u32);
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x922495e8
	ctx.lr = 0x92246AFC;
	sub_922495E8(ctx, base);
	// lwz r26,52(r31)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r11,48(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// cmplw cr6,r26,r11
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r11.u32, ctx.xer);
	// bge cr6,0x92246b1c
	if (!ctx.cr6.lt) goto loc_92246B1C;
	// subf r10,r26,r11
	ctx.r10.u64 = ctx.r11.u64 - ctx.r26.u64;
	// addi r23,r10,-1
	ctx.r23.s64 = ctx.r10.s64 + -1;
	// b 0x92246b24
	goto loc_92246B24;
loc_92246B1C:
	// lwz r10,44(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// subf r23,r26,r10
	ctx.r23.u64 = ctx.r10.u64 - ctx.r26.u64;
loc_92246B24:
	// lwz r9,44(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// cmplw cr6,r26,r9
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r9.u32, ctx.xer);
	// bne cr6,0x92246b58
	if (!ctx.cr6.eq) goto loc_92246B58;
	// lwz r10,40(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// beq cr6,0x92246b58
	if (ctx.cr6.eq) goto loc_92246B58;
	// mr r26,r10
	ctx.r26.u64 = ctx.r10.u64;
	// cmplw cr6,r26,r11
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r11.u32, ctx.xer);
	// bge cr6,0x92246b54
	if (!ctx.cr6.lt) goto loc_92246B54;
	// subf r11,r26,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r26.u64;
	// addi r23,r11,-1
	ctx.r23.s64 = ctx.r11.s64 + -1;
	// b 0x92246b58
	goto loc_92246B58;
loc_92246B54:
	// subf r23,r26,r9
	ctx.r23.u64 = ctx.r9.u64 - ctx.r26.u64;
loc_92246B58:
	// cmplwi cr6,r23,0
	ctx.cr6.compare<uint32_t>(ctx.r23.u32, 0, ctx.xer);
	// beq cr6,0x92246fcc
	if (ctx.cr6.eq) goto loc_92246FCC;
loc_92246B60:
	// lwz r25,4(r31)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// cmplw cr6,r25,r24
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, ctx.r24.u32, ctx.xer);
	// ble cr6,0x92246b74
	if (!ctx.cr6.gt) goto loc_92246B74;
	// mr r25,r24
	ctx.r25.u64 = ctx.r24.u64;
loc_92246B74:
	// cmplw cr6,r25,r23
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, ctx.r23.u32, ctx.xer);
	// ble cr6,0x92246b80
	if (!ctx.cr6.gt) goto loc_92246B80;
	// mr r25,r23
	ctx.r25.u64 = ctx.r23.u64;
loc_92246B80:
	// mr r5,r25
	ctx.r5.u64 = ctx.r25.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205b680
	ctx.lr = 0x92246B90;
	sub_9205B680(ctx, base);
	// lwz r11,4(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// add r29,r25,r29
	ctx.r29.u64 = ctx.r25.u64 + ctx.r29.u64;
	// subf. r11,r25,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r25.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// subf r24,r25,r24
	ctx.r24.u64 = ctx.r24.u64 - ctx.r25.u64;
	// add r26,r25,r26
	ctx.r26.u64 = ctx.r25.u64 + ctx.r26.u64;
	// subf r23,r25,r23
	ctx.r23.u64 = ctx.r23.u64 - ctx.r25.u64;
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// bne 0x92246fbc
	if (!ctx.cr0.eq) goto loc_92246FBC;
	// b 0x92246a80
	goto loc_92246A80;
loc_92246BB4:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r11,r11,r28
	ctx.r11.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r11,r27
	ctx.r27.u64 = ctx.r11.u64 | ctx.r27.u64;
loc_92246BD8:
	// cmplwi cr6,r28,14
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 14, ctx.xer);
	// blt cr6,0x92246bb4
	if (ctx.cr6.lt) goto loc_92246BB4;
	// clrlwi r11,r27,18
	ctx.r11.u64 = ctx.r27.u32 & 0x3FFF;
	// clrlwi r10,r11,27
	ctx.r10.u64 = ctx.r11.u32 & 0x1F;
	// cmplwi cr6,r10,29
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 29, ctx.xer);
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// bgt cr6,0x9224703c
	if (ctx.cr6.gt) goto loc_9224703C;
	// rlwinm r11,r11,27,27,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1F;
	// cmplwi cr6,r11,29
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 29, ctx.xer);
	// bgt cr6,0x9224703c
	if (ctx.cr6.gt) goto loc_9224703C;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r10,32(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// li r5,4
	ctx.r5.s64 = 4;
	// addi r4,r11,258
	ctx.r4.s64 = ctx.r11.s64 + 258;
	// mtctr r10
	ctx.ctr.u64 = ctx.r10.u64;
	// bctrl 
	ctx.lr = 0x92246C1C;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// stw r3,12(r31)
	REX_STORE_U32(ctx.r31.u32 + 12, ctx.r3.u32);
	// beq 0x9224701c
	if (ctx.cr0.eq) goto loc_9224701C;
	// li r11,4
	ctx.r11.s64 = 4;
	// stw r21,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r21.u32);
	// rlwinm r27,r27,18,14,31
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 18) & 0x3FFFF;
	// addi r28,r28,-14
	ctx.r28.s64 = ctx.r28.s64 + -14;
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
	// b 0x92246c9c
	goto loc_92246C9C;
loc_92246C40:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r11,r11,r28
	ctx.r11.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r11,r27
	ctx.r27.u64 = ctx.r11.u64 | ctx.r27.u64;
loc_92246C64:
	// cmplwi cr6,r28,3
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 3, ctx.xer);
	// blt cr6,0x92246c40
	if (ctx.cr6.lt) goto loc_92246C40;
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// clrlwi r9,r27,29
	ctx.r9.u64 = ctx.r27.u32 & 0x7;
	// lwz r10,12(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// rlwinm r27,r27,29,3,31
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 29) & 0x1FFFFFFF;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r28,r28,-3
	ctx.r28.s64 = ctx.r28.s64 + -3;
	// lwzx r11,r11,r17
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r17.u32);
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// stwx r9,r11,r10
	REX_STORE_U32(ctx.r11.u32 + ctx.r10.u32, ctx.r9.u32);
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r11.u32);
loc_92246C9C:
	// lwz r11,4(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// lwz r10,8(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// rlwinm r11,r11,22,10,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 22) & 0x3FFFFF;
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// cmplw cr6,r10,r11
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x92246c64
	if (ctx.cr6.lt) goto loc_92246C64;
	// b 0x92246cdc
	goto loc_92246CDC;
loc_92246CB8:
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// lwz r10,12(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// lwzx r11,r11,r17
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r17.u32);
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// stwx r21,r11,r10
	REX_STORE_U32(ctx.r11.u32 + ctx.r10.u32, ctx.r21.u32);
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r11.u32);
loc_92246CDC:
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// cmplwi cr6,r11,19
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 19, ctx.xer);
	// blt cr6,0x92246cb8
	if (ctx.cr6.lt) goto loc_92246CB8;
	// addi r4,r31,16
	ctx.r4.s64 = ctx.r31.s64 + 16;
	// lwz r6,36(r31)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// lwz r3,12(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// addi r5,r31,20
	ctx.r5.s64 = ctx.r31.s64 + 20;
	// stw r16,0(r4)
	REX_STORE_U32(ctx.r4.u32 + 0, ctx.r16.u32);
	// bl 0x92249318
	ctx.lr = 0x92246D04;
	sub_92249318(ctx, base);
	// mr. r25,r3
	ctx.r25.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r25.s32, 0, ctx.xer);
	// bne 0x92247048
	if (!ctx.cr0.eq) goto loc_92247048;
	// li r11,5
	ctx.r11.s64 = 5;
	// stw r21,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r21.u32);
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
	// b 0x92246e7c
	goto loc_92246E7C;
loc_92246D1C:
	// lwz r11,16(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 16);
	// b 0x92246d48
	goto loc_92246D48;
loc_92246D24:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r10,0(r29)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r10,r10,r28
	ctx.r10.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r10,r27
	ctx.r27.u64 = ctx.r10.u64 | ctx.r27.u64;
loc_92246D48:
	// cmplw cr6,r28,r11
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x92246d24
	if (ctx.cr6.lt) goto loc_92246D24;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r10,20(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 20);
	// lwzx r11,r11,r19
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r19.u32);
	// and r11,r11,r27
	ctx.r11.u64 = ctx.r11.u64 & ctx.r27.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// lwz r5,4(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 4);
	// lbz r11,1(r11)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r11.u32 + 1);
	// cmplwi cr6,r5,16
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 16, ctx.xer);
	// bge cr6,0x92246da0
	if (!ctx.cr6.lt) goto loc_92246DA0;
	// lwz r10,8(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// subf r28,r11,r28
	ctx.r28.u64 = ctx.r28.u64 - ctx.r11.u64;
	// lwz r9,12(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// srw r27,r27,r11
	ctx.r27.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r11.u8 & 0x3F));
	// rlwinm r10,r10,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// stwx r5,r10,r9
	REX_STORE_U32(ctx.r10.u32 + ctx.r9.u32, ctx.r5.u32);
	// lwz r10,8(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// b 0x92246e7c
	goto loc_92246E7C;
loc_92246DA0:
	// cmplwi cr6,r5,18
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 18, ctx.xer);
	// bne cr6,0x92246db4
	if (!ctx.cr6.eq) goto loc_92246DB4;
	// mr r9,r16
	ctx.r9.u64 = ctx.r16.u64;
	// li r6,11
	ctx.r6.s64 = 11;
	// b 0x92246dbc
	goto loc_92246DBC;
loc_92246DB4:
	// addi r9,r5,-14
	ctx.r9.s64 = ctx.r5.s64 + -14;
	// li r6,3
	ctx.r6.s64 = 3;
loc_92246DBC:
	// add r10,r9,r11
	ctx.r10.u64 = ctx.r9.u64 + ctx.r11.u64;
	// b 0x92246de8
	goto loc_92246DE8;
loc_92246DC4:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92247008
	if (ctx.cr6.eq) goto loc_92247008;
	// lbz r8,0(r29)
	ctx.r8.u64 = REX_LOAD_U8(ctx.r29.u32 + 0);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r29,r29,1
	ctx.r29.s64 = ctx.r29.s64 + 1;
	// slw r8,r8,r28
	ctx.r8.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r28.u8 & 0x3F));
	// addi r28,r28,8
	ctx.r28.s64 = ctx.r28.s64 + 8;
	// or r27,r8,r27
	ctx.r27.u64 = ctx.r8.u64 | ctx.r27.u64;
loc_92246DE8:
	// cmplw cr6,r28,r10
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r10.u32, ctx.xer);
	// blt cr6,0x92246dc4
	if (ctx.cr6.lt) goto loc_92246DC4;
	// subf r8,r9,r28
	ctx.r8.u64 = ctx.r28.u64 - ctx.r9.u64;
	// rlwinm r10,r9,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 2) & 0xFFFFFFFC;
	// subf r28,r11,r8
	ctx.r28.u64 = ctx.r8.u64 - ctx.r11.u64;
	// srw r11,r27,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r11.u8 & 0x3F));
	// lwzx r8,r10,r19
	ctx.r8.u64 = REX_LOAD_U32(ctx.r10.u32 + ctx.r19.u32);
	// lwz r10,4(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// and r8,r8,r11
	ctx.r8.u64 = ctx.r8.u64 & ctx.r11.u64;
	// rlwinm r7,r10,27,27,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 27) & 0x1F;
	// clrlwi r10,r10,27
	ctx.r10.u64 = ctx.r10.u32 & 0x1F;
	// add r8,r8,r6
	ctx.r8.u64 = ctx.r8.u64 + ctx.r6.u64;
	// add r10,r7,r10
	ctx.r10.u64 = ctx.r7.u64 + ctx.r10.u64;
	// addi r10,r10,258
	ctx.r10.s64 = ctx.r10.s64 + 258;
	// srw r27,r11,r9
	ctx.r27.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r11.u32 >> (ctx.r9.u8 & 0x3F));
	// lwz r11,8(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// add r9,r8,r11
	ctx.r9.u64 = ctx.r8.u64 + ctx.r11.u64;
	// cmplw cr6,r9,r10
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r10.u32, ctx.xer);
	// bgt cr6,0x92247070
	if (ctx.cr6.gt) goto loc_92247070;
	// cmplwi cr6,r5,16
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 16, ctx.xer);
	// bne cr6,0x92246e58
	if (!ctx.cr6.eq) goto loc_92246E58;
	// cmplwi cr6,r11,1
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 1, ctx.xer);
	// blt cr6,0x92247070
	if (ctx.cr6.lt) goto loc_92247070;
	// lwz r9,12(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// rlwinm r10,r11,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r10,r10,r9
	ctx.r10.u64 = ctx.r10.u64 + ctx.r9.u64;
	// lwz r9,-4(r10)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r10.u32 + -4);
	// b 0x92246e5c
	goto loc_92246E5C;
loc_92246E58:
	// mr r9,r21
	ctx.r9.u64 = ctx.r21.u64;
loc_92246E5C:
	// rlwinm r10,r11,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
loc_92246E60:
	// lwz r7,12(r31)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// addic. r8,r8,-1
	ctx.xer.ca = ctx.r8.u32 > 0;
	ctx.r8.s64 = ctx.r8.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stwx r9,r7,r10
	REX_STORE_U32(ctx.r7.u32 + ctx.r10.u32, ctx.r9.u32);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// bne 0x92246e60
	if (!ctx.cr0.eq) goto loc_92246E60;
	// stw r11,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r11.u32);
loc_92246E7C:
	// lwz r11,4(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// lwz r9,8(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// rlwinm r10,r11,27,27,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1F;
	// clrlwi r11,r11,27
	ctx.r11.u64 = ctx.r11.u32 & 0x1F;
	// add r11,r10,r11
	ctx.r11.u64 = ctx.r10.u64 + ctx.r11.u64;
	// addi r11,r11,258
	ctx.r11.s64 = ctx.r11.s64 + 258;
	// cmplw cr6,r9,r11
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x92246d1c
	if (ctx.cr6.lt) goto loc_92246D1C;
	// lwz r11,4(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// addi r9,r1,120
	ctx.r9.s64 = ctx.r1.s64 + 120;
	// addi r8,r1,124
	ctx.r8.s64 = ctx.r1.s64 + 124;
	// lwz r10,36(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// rlwinm r4,r11,27,27,31
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1F;
	// lwz r5,12(r31)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// clrlwi r11,r11,27
	ctx.r11.u64 = ctx.r11.u32 & 0x1F;
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// addi r7,r1,96
	ctx.r7.s64 = ctx.r1.s64 + 96;
	// stw r21,20(r31)
	REX_STORE_U32(ctx.r31.u32 + 20, ctx.r21.u32);
	// addi r6,r1,100
	ctx.r6.s64 = ctx.r1.s64 + 100;
	// stw r20,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r20.u32);
	// addi r4,r4,1
	ctx.r4.s64 = ctx.r4.s64 + 1;
	// stw r18,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r18.u32);
	// addi r3,r11,257
	ctx.r3.s64 = ctx.r11.s64 + 257;
	// bl 0x922493f8
	ctx.lr = 0x92246EDC;
	sub_922493F8(ctx, base);
	// mr r25,r3
	ctx.r25.u64 = ctx.r3.u64;
	// lwz r4,12(r31)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r11,36(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92246EF4;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// cmplwi cr6,r25,0
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 0, ctx.xer);
	// bne cr6,0x92247090
	if (!ctx.cr6.eq) goto loc_92247090;
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// lwz r6,120(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + 120);
	// lwz r5,124(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 124);
	// lwz r4,96(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// lwz r3,100(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// bl 0x921c32f8
	ctx.lr = 0x92246F14;
	sub_921C32F8(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224701c
	if (ctx.cr0.eq) goto loc_9224701C;
	// stw r3,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r3.u32);
	// stw r18,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r18.u32);
loc_92246F24:
	// stw r27,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r27.u32);
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// stw r28,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r28.u32);
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// lwz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// lwz r10,8(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 8);
	// subf r11,r11,r29
	ctx.r11.u64 = ctx.r29.u64 - ctx.r11.u64;
	// stw r24,4(r30)
	REX_STORE_U32(ctx.r30.u32 + 4, ctx.r24.u32);
	// stw r29,0(r30)
	REX_STORE_U32(ctx.r30.u32 + 0, ctx.r29.u32);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// stw r11,8(r30)
	REX_STORE_U32(ctx.r30.u32 + 8, ctx.r11.u32);
	// stw r26,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r26.u32);
	// bl 0x92248840
	ctx.lr = 0x92246F5C;
	sub_92248840(ctx, base);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// cmpwi cr6,r5,1
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 1, ctx.xer);
	// bne cr6,0x92246ff8
	if (!ctx.cr6.eq) goto loc_92246FF8;
	// lwz r3,4(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// mr r22,r21
	ctx.r22.u64 = ctx.r21.u64;
	// bl 0x92248e80
	ctx.lr = 0x92246F78;
	sub_92248E80(ctx, base);
	// lwz r26,52(r31)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r11,48(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// lwz r29,0(r30)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwz r24,4(r30)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r30.u32 + 4);
	// cmplw cr6,r26,r11
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r11.u32, ctx.xer);
	// lwz r27,32(r31)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r31.u32 + 32);
	// lwz r28,28(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// bge cr6,0x92246fa4
	if (!ctx.cr6.lt) goto loc_92246FA4;
	// subf r11,r26,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r26.u64;
	// addi r23,r11,-1
	ctx.r23.s64 = ctx.r11.s64 + -1;
	// b 0x92246fac
	goto loc_92246FAC;
loc_92246FA4:
	// lwz r11,44(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// subf r23,r26,r11
	ctx.r23.u64 = ctx.r11.u64 - ctx.r26.u64;
loc_92246FAC:
	// lwz r11,24(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 24);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x92247098
	if (!ctx.cr6.eq) goto loc_92247098;
	// stw r21,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r21.u32);
loc_92246FBC:
	// lwz r10,0(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// cmplwi cr6,r10,9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 9, ctx.xer);
	// ble cr6,0x92246900
	if (!ctx.cr6.gt) goto loc_92246900;
loc_92246FC8:
	// li r5,-2
	ctx.r5.s64 = -2;
loc_92246FCC:
	// stw r27,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r27.u32);
	// stw r28,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r28.u32);
loc_92246FD4:
	// stw r24,4(r30)
	REX_STORE_U32(ctx.r30.u32 + 4, ctx.r24.u32);
loc_92246FD8:
	// lwz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// lwz r10,8(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 8);
	// subf r11,r11,r29
	ctx.r11.u64 = ctx.r29.u64 - ctx.r11.u64;
	// stw r29,0(r30)
	REX_STORE_U32(ctx.r30.u32 + 0, ctx.r29.u32);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// stw r11,8(r30)
	REX_STORE_U32(ctx.r30.u32 + 8, ctx.r11.u32);
	// stw r26,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r26.u32);
loc_92246FF8:
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x922495e8
	ctx.lr = 0x92247000;
	sub_922495E8(ctx, base);
	// addi r1,r1,272
	ctx.r1.s64 = ctx.r1.s64 + 272;
	// b 0x9205b498
	__restgprlr_16(ctx, base);
	return;
loc_92247008:
	// stw r27,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r27.u32);
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// stw r28,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r28.u32);
	// stw r21,4(r30)
	REX_STORE_U32(ctx.r30.u32 + 4, ctx.r21.u32);
	// b 0x92246fd8
	goto loc_92246FD8;
loc_9224701C:
	// li r5,-4
	ctx.r5.s64 = -4;
	// b 0x92246fcc
	goto loc_92246FCC;
loc_92247024:
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,19876
	ctx.r11.s64 = ctx.r11.s64 + 19876;
loc_9224702C:
	// stw r20,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r20.u32);
	// stw r11,24(r30)
	REX_STORE_U32(ctx.r30.u32 + 24, ctx.r11.u32);
loc_92247034:
	// li r5,-3
	ctx.r5.s64 = -3;
	// b 0x92246fcc
	goto loc_92246FCC;
loc_9224703C:
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,19840
	ctx.r11.s64 = ctx.r11.s64 + 19840;
	// b 0x9224702c
	goto loc_9224702C;
loc_92247048:
	// lwz r4,12(r31)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r11,36(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x9224705C;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// cmpwi cr6,r25,-3
	ctx.cr6.compare<int32_t>(ctx.r25.s32, -3, ctx.xer);
loc_92247060:
	// bne cr6,0x92247068
	if (!ctx.cr6.eq) goto loc_92247068;
	// stw r20,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r20.u32);
loc_92247068:
	// mr r5,r25
	ctx.r5.u64 = ctx.r25.u64;
	// b 0x92246fcc
	goto loc_92246FCC;
loc_92247070:
	// lwz r4,12(r31)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// lwz r3,40(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r11,36(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92247084;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,19812
	ctx.r11.s64 = ctx.r11.s64 + 19812;
	// b 0x9224702c
	goto loc_9224702C;
loc_92247090:
	// cmpwi cr6,r25,-3
	ctx.cr6.compare<int32_t>(ctx.r25.s32, -3, ctx.xer);
	// b 0x92247060
	goto loc_92247060;
loc_92247098:
	// stw r16,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r16.u32);
loc_9224709C:
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// stw r26,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r26.u32);
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x922495e8
	ctx.lr = 0x922470B0;
	sub_922495E8(ctx, base);
	// lwz r26,52(r31)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r11,48(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// cmplw cr6,r11,r26
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r26.u32, ctx.xer);
	// bne cr6,0x92246fcc
	if (!ctx.cr6.eq) goto loc_92246FCC;
	// li r11,8
	ctx.r11.s64 = 8;
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
loc_922470CC:
	// li r5,1
	ctx.r5.s64 = 1;
	// b 0x92246fcc
	goto loc_92246FCC;
}

DEFINE_REX_FUNC(sub_922470D8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r30,-24(r1)
	REX_STORE_U64(ctx.r1.u32 + -24, ctx.r30.u64);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// li r5,0
	ctx.r5.s64 = 0;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r31,r4
	ctx.r31.u64 = ctx.r4.u64;
	// bl 0x921c29e8
	ctx.lr = 0x922470FC;
	sub_921C29E8(ctx, base);
	// lwz r4,40(r30)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r11,36(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// lwz r3,40(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92247110;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// lwz r4,36(r30)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// lwz r3,40(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// lwz r11,36(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92247124;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// lwz r3,40(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// lwz r11,36(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92247138;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// li r3,0
	ctx.r3.s64 = 0;
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r30,-24(r1)
	ctx.r30.u64 = REX_LOAD_U64(ctx.r1.u32 + -24);
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_92247158) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b470
	ctx.lr = 0x92247160;
	__savegprlr_26(ctx, base);
	// addi r12,r1,-56
	ctx.r12.s64 = ctx.r1.s64 + -56;
	// bl 0x921f253c
	ctx.lr = 0x92247168;
	__savefpr_25(ctx, base);
	// lwz r9,328(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// mr r10,r5
	ctx.r10.u64 = ctx.r5.u64;
	// lwz r8,80(r4)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// lis r31,-28157
	ctx.r31.s64 = -1845297152;
	// lis r3,-28157
	ctx.r3.s64 = -1845297152;
	// lis r4,-28157
	ctx.r4.s64 = -1845297152;
	// lis r5,-28157
	ctx.r5.s64 = -1845297152;
	// addi r11,r1,-368
	ctx.r11.s64 = ctx.r1.s64 + -368;
	// lfs f30,31700(r31)
	ctx.fpscr.disableFlushMode();
	temp.u32 = REX_LOAD_U32(ctx.r31.u32 + 31700);
	ctx.f30.f64 = double(temp.f32);
	// addi r9,r9,128
	ctx.r9.s64 = ctx.r9.s64 + 128;
	// lfs f31,31696(r3)
	temp.u32 = REX_LOAD_U32(ctx.r3.u32 + 31696);
	ctx.f31.f64 = double(temp.f32);
	// li r30,8
	ctx.r30.s64 = 8;
	// lfs f1,31692(r4)
	temp.u32 = REX_LOAD_U32(ctx.r4.u32 + 31692);
	ctx.f1.f64 = double(temp.f32);
	// lfs f0,31688(r5)
	temp.u32 = REX_LOAD_U32(ctx.r5.u32 + 31688);
	ctx.f0.f64 = double(temp.f32);
loc_922471A0:
	// lhz r5,16(r10)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r10.u32 + 16);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r4,32(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 32);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r3,48(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 48);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r4,64(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 64);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r3,80(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 80);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r4,96(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 96);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r3,112(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 112);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x9224723c
	if (!ctx.cr6.eq) goto loc_9224723C;
	// lhz r5,0(r10)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// lfs f13,0(r8)
	ctx.fpscr.disableFlushMode();
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 0);
	ctx.f13.f64 = double(temp.f32);
	// extsh r3,r5
	ctx.r3.s64 = ctx.r5.s16;
	// std r3,-408(r1)
	REX_STORE_U64(ctx.r1.u32 + -408, ctx.r3.u64);
	// lfd f12,-408(r1)
	ctx.f12.u64 = REX_LOAD_U64(ctx.r1.u32 + -408);
	// fcfid f11,f12
	ctx.f11.f64 = double(ctx.f12.s64);
	// frsp f10,f11
	ctx.f10.f64 = double(float(ctx.f11.f64));
	// fmuls f13,f10,f13
	ctx.f13.f64 = double(float(ctx.f10.f64 * ctx.f13.f64));
	// stfs f13,0(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 0, temp.u32);
	// stfs f13,32(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 32, temp.u32);
	// stfs f13,64(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 64, temp.u32);
	// stfs f13,96(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 96, temp.u32);
	// stfs f13,128(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 128, temp.u32);
	// stfs f13,160(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 160, temp.u32);
	// stfs f13,192(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 192, temp.u32);
	// stfs f13,224(r11)
	temp.f32 = float(ctx.f13.f64);
	REX_STORE_U32(ctx.r11.u32 + 224, temp.u32);
	// b 0x922473d0
	goto loc_922473D0;
loc_9224723C:
	// lhz r4,32(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 32);
	// extsw r5,r5
	ctx.r5.s64 = ctx.r5.s32;
	// lhz r3,96(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 96);
	// lfs f9,64(r8)
	ctx.fpscr.disableFlushMode();
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 64);
	ctx.f9.f64 = double(temp.f32);
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// lhz r31,0(r10)
	ctx.r31.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// lhz r29,64(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 64);
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// lhz r27,80(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 80);
	// lhz r28,48(r10)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r10.u32 + 48);
	// lfs f8,192(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 192);
	ctx.f8.f64 = double(temp.f32);
	// lhz r26,112(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + 112);
	// lfs f7,0(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 0);
	ctx.f7.f64 = double(temp.f32);
	// std r4,-424(r1)
	REX_STORE_U64(ctx.r1.u32 + -424, ctx.r4.u64);
	// extsh r4,r29
	ctx.r4.s64 = ctx.r29.s16;
	// std r3,-440(r1)
	REX_STORE_U64(ctx.r1.u32 + -440, ctx.r3.u64);
	// extsh r3,r28
	ctx.r3.s64 = ctx.r28.s16;
	// std r31,-448(r1)
	REX_STORE_U64(ctx.r1.u32 + -448, ctx.r31.u64);
	// extsh r31,r27
	ctx.r31.s64 = ctx.r27.s16;
	// std r5,-392(r1)
	REX_STORE_U64(ctx.r1.u32 + -392, ctx.r5.u64);
	// lfs f6,128(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 128);
	ctx.f6.f64 = double(temp.f32);
	// lfs f4,160(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 160);
	ctx.f4.f64 = double(temp.f32);
	// std r4,-416(r1)
	REX_STORE_U64(ctx.r1.u32 + -416, ctx.r4.u64);
	// extsh r4,r26
	ctx.r4.s64 = ctx.r26.s16;
	// std r3,-400(r1)
	REX_STORE_U64(ctx.r1.u32 + -400, ctx.r3.u64);
	// lfs f5,96(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 96);
	ctx.f5.f64 = double(temp.f32);
	// std r31,-432(r1)
	REX_STORE_U64(ctx.r1.u32 + -432, ctx.r31.u64);
	// lfs f3,32(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 32);
	ctx.f3.f64 = double(temp.f32);
	// lfs f2,224(r8)
	temp.u32 = REX_LOAD_U32(ctx.r8.u32 + 224);
	ctx.f2.f64 = double(temp.f32);
	// std r4,-384(r1)
	REX_STORE_U64(ctx.r1.u32 + -384, ctx.r4.u64);
	// lfd f13,-424(r1)
	ctx.f13.u64 = REX_LOAD_U64(ctx.r1.u32 + -424);
	// lfd f12,-440(r1)
	ctx.f12.u64 = REX_LOAD_U64(ctx.r1.u32 + -440);
	// fcfid f11,f13
	ctx.f11.f64 = double(ctx.f13.s64);
	// fcfid f10,f12
	ctx.f10.f64 = double(ctx.f12.s64);
	// lfd f13,-448(r1)
	ctx.f13.u64 = REX_LOAD_U64(ctx.r1.u32 + -448);
	// fcfid f13,f13
	ctx.f13.f64 = double(ctx.f13.s64);
	// lfd f27,-392(r1)
	ctx.f27.u64 = REX_LOAD_U64(ctx.r1.u32 + -392);
	// fcfid f27,f27
	ctx.f27.f64 = double(ctx.f27.s64);
	// lfd f12,-416(r1)
	ctx.f12.u64 = REX_LOAD_U64(ctx.r1.u32 + -416);
	// fcfid f12,f12
	ctx.f12.f64 = double(ctx.f12.s64);
	// lfd f29,-400(r1)
	ctx.f29.u64 = REX_LOAD_U64(ctx.r1.u32 + -400);
	// lfd f28,-432(r1)
	ctx.f28.u64 = REX_LOAD_U64(ctx.r1.u32 + -432);
	// fcfid f29,f29
	ctx.f29.f64 = double(ctx.f29.s64);
	// fcfid f28,f28
	ctx.f28.f64 = double(ctx.f28.s64);
	// lfd f26,-384(r1)
	ctx.f26.u64 = REX_LOAD_U64(ctx.r1.u32 + -384);
	// frsp f11,f11
	ctx.f11.f64 = double(float(ctx.f11.f64));
	// frsp f10,f10
	ctx.f10.f64 = double(float(ctx.f10.f64));
	// frsp f13,f13
	ctx.f13.f64 = double(float(ctx.f13.f64));
	// fcfid f26,f26
	ctx.f26.f64 = double(ctx.f26.s64);
	// frsp f27,f27
	ctx.f27.f64 = double(float(ctx.f27.f64));
	// frsp f25,f12
	ctx.f25.f64 = double(float(ctx.f12.f64));
	// frsp f29,f29
	ctx.f29.f64 = double(float(ctx.f29.f64));
	// frsp f28,f28
	ctx.f28.f64 = double(float(ctx.f28.f64));
	// fmuls f12,f11,f9
	ctx.f12.f64 = double(float(ctx.f11.f64 * ctx.f9.f64));
	// fmuls f11,f10,f8
	ctx.f11.f64 = double(float(ctx.f10.f64 * ctx.f8.f64));
	// fmuls f10,f13,f7
	ctx.f10.f64 = double(float(ctx.f13.f64 * ctx.f7.f64));
	// frsp f26,f26
	ctx.f26.f64 = double(float(ctx.f26.f64));
	// fmuls f9,f25,f6
	ctx.f9.f64 = double(float(ctx.f25.f64 * ctx.f6.f64));
	// fmuls f8,f29,f5
	ctx.f8.f64 = double(float(ctx.f29.f64 * ctx.f5.f64));
	// fmuls f7,f28,f4
	ctx.f7.f64 = double(float(ctx.f28.f64 * ctx.f4.f64));
	// fmuls f6,f3,f27
	ctx.f6.f64 = double(float(ctx.f3.f64 * ctx.f27.f64));
	// fadds f13,f11,f12
	ctx.f13.f64 = double(float(ctx.f11.f64 + ctx.f12.f64));
	// fsubs f4,f12,f11
	ctx.f4.f64 = double(float(ctx.f12.f64 - ctx.f11.f64));
	// fmuls f5,f26,f2
	ctx.f5.f64 = double(float(ctx.f26.f64 * ctx.f2.f64));
	// fadds f12,f9,f10
	ctx.f12.f64 = double(float(ctx.f9.f64 + ctx.f10.f64));
	// fsubs f11,f10,f9
	ctx.f11.f64 = double(float(ctx.f10.f64 - ctx.f9.f64));
	// fadds f10,f7,f8
	ctx.f10.f64 = double(float(ctx.f7.f64 + ctx.f8.f64));
	// fmsubs f9,f4,f0,f13
	ctx.f9.f64 = double(float(std::fma(ctx.f4.f64, ctx.f0.f64, -ctx.f13.f64)));
	// fadds f4,f13,f12
	ctx.f4.f64 = double(float(ctx.f13.f64 + ctx.f12.f64));
	// fsubs f3,f12,f13
	ctx.f3.f64 = double(float(ctx.f12.f64 - ctx.f13.f64));
	// fsubs f12,f7,f8
	ctx.f12.f64 = double(float(ctx.f7.f64 - ctx.f8.f64));
	// fadds f8,f5,f6
	ctx.f8.f64 = double(float(ctx.f5.f64 + ctx.f6.f64));
	// fadds f2,f9,f11
	ctx.f2.f64 = double(float(ctx.f9.f64 + ctx.f11.f64));
	// fsubs f11,f11,f9
	ctx.f11.f64 = double(float(ctx.f11.f64 - ctx.f9.f64));
	// fsubs f9,f6,f5
	ctx.f9.f64 = double(float(ctx.f6.f64 - ctx.f5.f64));
	// fadds f13,f8,f10
	ctx.f13.f64 = double(float(ctx.f8.f64 + ctx.f10.f64));
	// fsubs f6,f8,f10
	ctx.f6.f64 = double(float(ctx.f8.f64 - ctx.f10.f64));
	// fadds f7,f9,f12
	ctx.f7.f64 = double(float(ctx.f9.f64 + ctx.f12.f64));
	// fadds f5,f13,f4
	ctx.f5.f64 = double(float(ctx.f13.f64 + ctx.f4.f64));
	// fmuls f10,f7,f1
	ctx.f10.f64 = double(float(ctx.f7.f64 * ctx.f1.f64));
	// fnmsubs f12,f12,f31,f10
	ctx.f12.f64 = double(float(-std::fma(ctx.f12.f64, ctx.f31.f64, -ctx.f10.f64)));
	// stfs f5,0(r11)
	temp.f32 = float(ctx.f5.f64);
	REX_STORE_U32(ctx.r11.u32 + 0, temp.u32);
	// fsubs f4,f4,f13
	ctx.f4.f64 = double(float(ctx.f4.f64 - ctx.f13.f64));
	// stfs f4,224(r11)
	temp.f32 = float(ctx.f4.f64);
	REX_STORE_U32(ctx.r11.u32 + 224, temp.u32);
	// fmsubs f10,f9,f30,f10
	ctx.f10.f64 = double(float(std::fma(ctx.f9.f64, ctx.f30.f64, -ctx.f10.f64)));
	// fsubs f13,f12,f13
	ctx.f13.f64 = double(float(ctx.f12.f64 - ctx.f13.f64));
	// fmsubs f12,f6,f0,f13
	ctx.f12.f64 = double(float(std::fma(ctx.f6.f64, ctx.f0.f64, -ctx.f13.f64)));
	// fadds f9,f13,f2
	ctx.f9.f64 = double(float(ctx.f13.f64 + ctx.f2.f64));
	// stfs f9,32(r11)
	temp.f32 = float(ctx.f9.f64);
	REX_STORE_U32(ctx.r11.u32 + 32, temp.u32);
	// fsubs f8,f2,f13
	ctx.f8.f64 = double(float(ctx.f2.f64 - ctx.f13.f64));
	// stfs f8,192(r11)
	temp.f32 = float(ctx.f8.f64);
	REX_STORE_U32(ctx.r11.u32 + 192, temp.u32);
	// fadds f13,f10,f12
	ctx.f13.f64 = double(float(ctx.f10.f64 + ctx.f12.f64));
	// fadds f7,f12,f11
	ctx.f7.f64 = double(float(ctx.f12.f64 + ctx.f11.f64));
	// stfs f7,64(r11)
	temp.f32 = float(ctx.f7.f64);
	REX_STORE_U32(ctx.r11.u32 + 64, temp.u32);
	// fsubs f6,f11,f12
	ctx.f6.f64 = double(float(ctx.f11.f64 - ctx.f12.f64));
	// stfs f6,160(r11)
	temp.f32 = float(ctx.f6.f64);
	REX_STORE_U32(ctx.r11.u32 + 160, temp.u32);
	// fadds f5,f13,f3
	ctx.f5.f64 = double(float(ctx.f13.f64 + ctx.f3.f64));
	// stfs f5,128(r11)
	temp.f32 = float(ctx.f5.f64);
	REX_STORE_U32(ctx.r11.u32 + 128, temp.u32);
	// fsubs f4,f3,f13
	ctx.f4.f64 = double(float(ctx.f3.f64 - ctx.f13.f64));
	// stfs f4,96(r11)
	temp.f32 = float(ctx.f4.f64);
	REX_STORE_U32(ctx.r11.u32 + 96, temp.u32);
loc_922473D0:
	// addi r30,r30,-1
	ctx.r30.s64 = ctx.r30.s64 + -1;
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// addi r8,r8,4
	ctx.r8.s64 = ctx.r8.s64 + 4;
	// addi r10,r10,2
	ctx.r10.s64 = ctx.r10.s64 + 2;
	// cmpwi cr6,r30,0
	ctx.cr6.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// bgt cr6,0x922471a0
	if (ctx.cr6.gt) goto loc_922471A0;
	// addi r11,r1,-360
	ctx.r11.s64 = ctx.r1.s64 + -360;
	// li r8,8
	ctx.r8.s64 = 8;
loc_922473F0:
	// lfs f13,8(r11)
	ctx.fpscr.disableFlushMode();
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 8);
	ctx.f13.f64 = double(temp.f32);
	// addi r3,r1,-392
	ctx.r3.s64 = ctx.r1.s64 + -392;
	// lfs f12,-8(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + -8);
	ctx.f12.f64 = double(temp.f32);
	// lwz r10,0(r6)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r6.u32 + 0);
	// lfs f11,16(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 16);
	ctx.f11.f64 = double(temp.f32);
	// fadds f5,f12,f13
	ctx.f5.f64 = double(float(ctx.f12.f64 + ctx.f13.f64));
	// lfs f10,0(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 0);
	ctx.f10.f64 = double(temp.f32);
	// fsubs f12,f12,f13
	ctx.f12.f64 = double(float(ctx.f12.f64 - ctx.f13.f64));
	// lfs f9,12(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 12);
	ctx.f9.f64 = double(temp.f32);
	// fadds f13,f11,f10
	ctx.f13.f64 = double(float(ctx.f11.f64 + ctx.f10.f64));
	// lfs f8,4(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 4);
	ctx.f8.f64 = double(temp.f32);
	// fsubs f3,f10,f11
	ctx.f3.f64 = double(float(ctx.f10.f64 - ctx.f11.f64));
	// lfs f7,20(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 20);
	ctx.f7.f64 = double(temp.f32);
	// fadds f11,f8,f9
	ctx.f11.f64 = double(float(ctx.f8.f64 + ctx.f9.f64));
	// lfs f6,-4(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + -4);
	ctx.f6.f64 = double(temp.f32);
	// fsubs f10,f9,f8
	ctx.f10.f64 = double(float(ctx.f9.f64 - ctx.f8.f64));
	// fadds f9,f7,f6
	ctx.f9.f64 = double(float(ctx.f7.f64 + ctx.f6.f64));
	// add r10,r7,r10
	ctx.r10.u64 = ctx.r7.u64 + ctx.r10.u64;
	// fsubs f8,f6,f7
	ctx.f8.f64 = double(float(ctx.f6.f64 - ctx.f7.f64));
	// addi r8,r8,-1
	ctx.r8.s64 = ctx.r8.s64 + -1;
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// fadds f7,f13,f5
	ctx.f7.f64 = double(float(ctx.f13.f64 + ctx.f5.f64));
	// fmsubs f6,f3,f0,f13
	ctx.f6.f64 = double(float(std::fma(ctx.f3.f64, ctx.f0.f64, -ctx.f13.f64)));
	// fsubs f5,f5,f13
	ctx.f5.f64 = double(float(ctx.f5.f64 - ctx.f13.f64));
	// fadds f13,f9,f11
	ctx.f13.f64 = double(float(ctx.f9.f64 + ctx.f11.f64));
	// fadds f2,f8,f10
	ctx.f2.f64 = double(float(ctx.f8.f64 + ctx.f10.f64));
	// fsubs f4,f9,f11
	ctx.f4.f64 = double(float(ctx.f9.f64 - ctx.f11.f64));
	// fadds f9,f6,f12
	ctx.f9.f64 = double(float(ctx.f6.f64 + ctx.f12.f64));
	// fsubs f12,f12,f6
	ctx.f12.f64 = double(float(ctx.f12.f64 - ctx.f6.f64));
	// fadds f3,f13,f7
	ctx.f3.f64 = double(float(ctx.f13.f64 + ctx.f7.f64));
	// fmuls f11,f2,f1
	ctx.f11.f64 = double(float(ctx.f2.f64 * ctx.f1.f64));
	// fsubs f2,f7,f13
	ctx.f2.f64 = double(float(ctx.f7.f64 - ctx.f13.f64));
	// fctiwz f7,f3
	ctx.f7.s64 = std::isnan(ctx.f3.f64) ? int64_t(0x80000000U) : (ctx.f3.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f3.f64));
	// stfiwx f7,0,r3
	REX_STORE_U32(ctx.r3.u32, ctx.f7.u32);
	// fnmsubs f6,f10,f31,f11
	ctx.f6.f64 = double(float(-std::fma(ctx.f10.f64, ctx.f31.f64, -ctx.f11.f64)));
	// fctiwz f3,f2
	ctx.f3.s64 = std::isnan(ctx.f2.f64) ? int64_t(0x80000000U) : (ctx.f2.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f2.f64));
	// fmsubs f2,f8,f30,f11
	ctx.f2.f64 = double(float(std::fma(ctx.f8.f64, ctx.f30.f64, -ctx.f11.f64)));
	// fsubs f13,f6,f13
	ctx.f13.f64 = double(float(ctx.f6.f64 - ctx.f13.f64));
	// fadds f11,f13,f9
	ctx.f11.f64 = double(float(ctx.f13.f64 + ctx.f9.f64));
	// fsubs f10,f9,f13
	ctx.f10.f64 = double(float(ctx.f9.f64 - ctx.f13.f64));
	// fmsubs f13,f4,f0,f13
	ctx.f13.f64 = double(float(std::fma(ctx.f4.f64, ctx.f0.f64, -ctx.f13.f64)));
	// fctiwz f9,f11
	ctx.f9.s64 = std::isnan(ctx.f11.f64) ? int64_t(0x80000000U) : (ctx.f11.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f11.f64));
	// fctiwz f8,f10
	ctx.f8.s64 = std::isnan(ctx.f10.f64) ? int64_t(0x80000000U) : (ctx.f10.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f10.f64));
	// fadds f7,f13,f12
	ctx.f7.f64 = double(float(ctx.f13.f64 + ctx.f12.f64));
	// fadds f11,f2,f13
	ctx.f11.f64 = double(float(ctx.f2.f64 + ctx.f13.f64));
	// fsubs f4,f12,f13
	ctx.f4.f64 = double(float(ctx.f12.f64 - ctx.f13.f64));
	// fctiwz f6,f7
	ctx.f6.s64 = std::isnan(ctx.f7.f64) ? int64_t(0x80000000U) : (ctx.f7.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f7.f64));
	// fsubs f2,f5,f11
	ctx.f2.f64 = double(float(ctx.f5.f64 - ctx.f11.f64));
	// lwz r5,-392(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -392);
	// addi r4,r1,-432
	ctx.r4.s64 = ctx.r1.s64 + -432;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f3,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f3.u32);
	// fadds f3,f11,f5
	ctx.f3.f64 = double(float(ctx.f11.f64 + ctx.f5.f64));
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r3.u8);
	// lwz r5,-432(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -432);
	// addi r4,r1,-400
	ctx.r4.s64 = ctx.r1.s64 + -400;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f9,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f9.u32);
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,7(r10)
	REX_STORE_U8(ctx.r10.u32 + 7, ctx.r3.u8);
	// lwz r5,-400(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -400);
	// addi r4,r1,-416
	ctx.r4.s64 = ctx.r1.s64 + -416;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f8,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f8.u32);
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,1(r10)
	REX_STORE_U8(ctx.r10.u32 + 1, ctx.r3.u8);
	// lwz r5,-416(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -416);
	// addi r4,r1,-448
	ctx.r4.s64 = ctx.r1.s64 + -448;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f6,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f6.u32);
	// clrlwi r3,r5,22
	ctx.r3.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r5,r3,r9
	ctx.r5.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r9.u32);
	// stb r5,6(r10)
	REX_STORE_U8(ctx.r10.u32 + 6, ctx.r5.u8);
	// lwz r5,-448(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -448);
	// addi r4,r1,-440
	ctx.r4.s64 = ctx.r1.s64 + -440;
	// fctiwz f13,f4
	ctx.f13.s64 = std::isnan(ctx.f4.f64) ? int64_t(0x80000000U) : (ctx.f4.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f4.f64));
	// addi r6,r6,4
	ctx.r6.s64 = ctx.r6.s64 + 4;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// fctiwz f12,f3
	ctx.f12.s64 = std::isnan(ctx.f3.f64) ? int64_t(0x80000000U) : (ctx.f3.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f3.f64));
	// fctiwz f11,f2
	ctx.f11.s64 = std::isnan(ctx.f2.f64) ? int64_t(0x80000000U) : (ctx.f2.f64 > double(INT_MAX)) ? INT_MAX : simde_mm_cvttsd_si32(simde_mm_load_sd(&ctx.f2.f64));
	// cmplwi cr6,r8,0
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f13,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f13.u32);
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,2(r10)
	REX_STORE_U8(ctx.r10.u32 + 2, ctx.r3.u8);
	// lwz r5,-440(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -440);
	// addi r4,r1,-424
	ctx.r4.s64 = ctx.r1.s64 + -424;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f12,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f12.u32);
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,5(r10)
	REX_STORE_U8(ctx.r10.u32 + 5, ctx.r3.u8);
	// lwz r5,-424(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -424);
	// addi r4,r1,-408
	ctx.r4.s64 = ctx.r1.s64 + -408;
	// addi r3,r5,4
	ctx.r3.s64 = ctx.r5.s64 + 4;
	// srawi r5,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r5.s64 = ctx.r3.s32 >> 3;
	// stfiwx f11,0,r4
	REX_STORE_U32(ctx.r4.u32, ctx.f11.u32);
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r3,r4,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r3,4(r10)
	REX_STORE_U8(ctx.r10.u32 + 4, ctx.r3.u8);
	// lwz r5,-408(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -408);
	// addi r5,r5,4
	ctx.r5.s64 = ctx.r5.s64 + 4;
	// srawi r4,r5,3
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x7) != 0);
	ctx.r4.s64 = ctx.r5.s32 >> 3;
	// clrlwi r3,r4,22
	ctx.r3.u64 = ctx.r4.u32 & 0x3FF;
	// lbzx r5,r3,r9
	ctx.r5.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r9.u32);
	// stb r5,3(r10)
	REX_STORE_U8(ctx.r10.u32 + 3, ctx.r5.u8);
	// bne cr6,0x922473f0
	if (!ctx.cr6.eq) goto loc_922473F0;
	// addi r12,r1,-56
	ctx.r12.s64 = ctx.r1.s64 + -56;
	// bl 0x921f2588
	ctx.lr = 0x922475CC;
	__restfpr_25(ctx, base);
	// b 0x9205b4c0
	__restgprlr_26(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_922475D0) {
	REX_FUNC_PROLOGUE();
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b454
	ctx.lr = 0x922475D8;
	__savegprlr_19(ctx, base);
	// lwz r9,328(r3)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// mr r8,r5
	ctx.r8.u64 = ctx.r5.u64;
	// lwz r10,80(r4)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// addi r11,r1,-368
	ctx.r11.s64 = ctx.r1.s64 + -368;
	// addi r9,r9,128
	ctx.r9.s64 = ctx.r9.s64 + 128;
	// li r24,8
	ctx.r24.s64 = 8;
loc_922475F0:
	// lhz r4,16(r8)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r8.u32 + 16);
	// lhz r5,32(r8)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r8.u32 + 32);
	// lhz r31,48(r8)
	ctx.r31.u64 = REX_LOAD_U16(ctx.r8.u32 + 48);
	// extsh r3,r4
	ctx.r3.s64 = ctx.r4.s16;
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// lhz r4,64(r8)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r8.u32 + 64);
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// lhz r29,80(r8)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r8.u32 + 80);
	// or r27,r3,r5
	ctx.r27.u64 = ctx.r3.u64 | ctx.r5.u64;
	// lhz r28,112(r8)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r8.u32 + 112);
	// extsh r30,r4
	ctx.r30.s64 = ctx.r4.s16;
	// lhz r4,96(r8)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r8.u32 + 96);
	// or r27,r27,r31
	ctx.r27.u64 = ctx.r27.u64 | ctx.r31.u64;
	// extsh r29,r29
	ctx.r29.s64 = ctx.r29.s16;
	// or r27,r27,r30
	ctx.r27.u64 = ctx.r27.u64 | ctx.r30.u64;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// or r27,r27,r29
	ctx.r27.u64 = ctx.r27.u64 | ctx.r29.u64;
	// extsh r28,r28
	ctx.r28.s64 = ctx.r28.s16;
	// or r27,r27,r4
	ctx.r27.u64 = ctx.r27.u64 | ctx.r4.u64;
	// or r27,r27,r28
	ctx.r27.u64 = ctx.r27.u64 | ctx.r28.u64;
	// extsh r27,r27
	ctx.r27.s64 = ctx.r27.s16;
	// cmpwi cr6,r27,0
	ctx.cr6.compare<int32_t>(ctx.r27.s32, 0, ctx.xer);
	// bne cr6,0x92247684
	if (!ctx.cr6.eq) goto loc_92247684;
	// lhz r3,0(r8)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r8.u32 + 0);
	// lhz r5,0(r10)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// extsh r4,r3
	ctx.r4.s64 = ctx.r3.s16;
	// extsh r3,r5
	ctx.r3.s64 = ctx.r5.s16;
	// mullw r5,r4,r3
	ctx.r5.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r3.s32);
	// stw r5,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r5.u32);
	// stw r5,32(r11)
	REX_STORE_U32(ctx.r11.u32 + 32, ctx.r5.u32);
	// stw r5,64(r11)
	REX_STORE_U32(ctx.r11.u32 + 64, ctx.r5.u32);
	// stw r5,96(r11)
	REX_STORE_U32(ctx.r11.u32 + 96, ctx.r5.u32);
	// stw r5,128(r11)
	REX_STORE_U32(ctx.r11.u32 + 128, ctx.r5.u32);
	// stw r5,160(r11)
	REX_STORE_U32(ctx.r11.u32 + 160, ctx.r5.u32);
	// stw r5,192(r11)
	REX_STORE_U32(ctx.r11.u32 + 192, ctx.r5.u32);
	// stw r5,224(r11)
	REX_STORE_U32(ctx.r11.u32 + 224, ctx.r5.u32);
	// b 0x92247828
	goto loc_92247828;
loc_92247684:
	// lhz r27,32(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 32);
	// lhz r26,96(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + 96);
	// extsh r27,r27
	ctx.r27.s64 = ctx.r27.s16;
	// lhz r25,0(r8)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r8.u32 + 0);
	// extsh r26,r26
	ctx.r26.s64 = ctx.r26.s16;
	// lhz r23,0(r10)
	ctx.r23.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// mullw r5,r27,r5
	ctx.r5.s64 = int64_t(ctx.r27.s32) * int64_t(ctx.r5.s32);
	// lhz r27,64(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 64);
	// lhz r22,16(r10)
	ctx.r22.u64 = REX_LOAD_U16(ctx.r10.u32 + 16);
	// lhz r21,48(r10)
	ctx.r21.u64 = REX_LOAD_U16(ctx.r10.u32 + 48);
	// lhz r20,80(r10)
	ctx.r20.u64 = REX_LOAD_U16(ctx.r10.u32 + 80);
	// lhz r19,112(r10)
	ctx.r19.u64 = REX_LOAD_U16(ctx.r10.u32 + 112);
	// mullw r26,r26,r4
	ctx.r26.s64 = int64_t(ctx.r26.s32) * int64_t(ctx.r4.s32);
	// mr r4,r5
	ctx.r4.u64 = ctx.r5.u64;
	// mr r5,r26
	ctx.r5.u64 = ctx.r26.u64;
	// extsh r26,r25
	ctx.r26.s64 = ctx.r25.s16;
	// extsh r25,r23
	ctx.r25.s64 = ctx.r23.s16;
	// extsh r27,r27
	ctx.r27.s64 = ctx.r27.s16;
	// extsh r23,r22
	ctx.r23.s64 = ctx.r22.s16;
	// mullw r26,r26,r25
	ctx.r26.s64 = int64_t(ctx.r26.s32) * int64_t(ctx.r25.s32);
	// mullw r30,r27,r30
	ctx.r30.s64 = int64_t(ctx.r27.s32) * int64_t(ctx.r30.s32);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// mullw r27,r23,r3
	ctx.r27.s64 = int64_t(ctx.r23.s32) * int64_t(ctx.r3.s32);
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// extsh r22,r21
	ctx.r22.s64 = ctx.r21.s16;
	// add r26,r4,r5
	ctx.r26.u64 = ctx.r4.u64 + ctx.r5.u64;
	// extsh r21,r20
	ctx.r21.s64 = ctx.r20.s16;
	// subf r4,r5,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r5.u64;
	// extsh r20,r19
	ctx.r20.s64 = ctx.r19.s16;
	// mullw r23,r21,r29
	ctx.r23.s64 = int64_t(ctx.r21.s32) * int64_t(ctx.r29.s32);
	// mr r5,r26
	ctx.r5.u64 = ctx.r26.u64;
	// mulli r26,r4,362
	ctx.r26.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(362));
	// mullw r29,r20,r28
	ctx.r29.s64 = int64_t(ctx.r20.s32) * int64_t(ctx.r28.s32);
	// mullw r25,r22,r31
	ctx.r25.s64 = int64_t(ctx.r22.s32) * int64_t(ctx.r31.s32);
	// extsh r4,r3
	ctx.r4.s64 = ctx.r3.s16;
	// extsh r3,r30
	ctx.r3.s64 = ctx.r30.s16;
	// extsh r30,r27
	ctx.r30.s64 = ctx.r27.s16;
	// extsh r31,r29
	ctx.r31.s64 = ctx.r29.s16;
	// extsh r29,r25
	ctx.r29.s64 = ctx.r25.s16;
	// extsh r28,r23
	ctx.r28.s64 = ctx.r23.s16;
	// srawi r27,r26,8
	ctx.xer.ca = (ctx.r26.s32 < 0) & ((ctx.r26.u32 & 0xFF) != 0);
	ctx.r27.s64 = ctx.r26.s32 >> 8;
	// add r26,r4,r3
	ctx.r26.u64 = ctx.r4.u64 + ctx.r3.u64;
	// add r25,r30,r31
	ctx.r25.u64 = ctx.r30.u64 + ctx.r31.u64;
	// subf r23,r31,r30
	ctx.r23.u64 = ctx.r30.u64 - ctx.r31.u64;
	// subf r3,r3,r4
	ctx.r3.u64 = ctx.r4.u64 - ctx.r3.u64;
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// subf r30,r29,r28
	ctx.r30.u64 = ctx.r28.u64 - ctx.r29.u64;
	// extsh r4,r26
	ctx.r4.s64 = ctx.r26.s16;
	// add r31,r29,r28
	ctx.r31.u64 = ctx.r29.u64 + ctx.r28.u64;
	// subf r27,r5,r27
	ctx.r27.u64 = ctx.r27.u64 - ctx.r5.u64;
	// extsh r28,r23
	ctx.r28.s64 = ctx.r23.s16;
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// add r26,r4,r5
	ctx.r26.u64 = ctx.r4.u64 + ctx.r5.u64;
	// extsh r29,r25
	ctx.r29.s64 = ctx.r25.s16;
	// subf r5,r5,r4
	ctx.r5.u64 = ctx.r4.u64 - ctx.r5.u64;
	// add r25,r30,r28
	ctx.r25.u64 = ctx.r30.u64 + ctx.r28.u64;
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// extsh r27,r27
	ctx.r27.s64 = ctx.r27.s16;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r26,r5
	ctx.r26.u64 = ctx.r5.u64;
	// add r5,r31,r29
	ctx.r5.u64 = ctx.r31.u64 + ctx.r29.u64;
	// add r23,r3,r27
	ctx.r23.u64 = ctx.r3.u64 + ctx.r27.u64;
	// mulli r25,r25,473
	ctx.r25.s64 = static_cast<int64_t>(ctx.r25.u64 * static_cast<uint64_t>(473));
	// mulli r30,r30,-669
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(-669));
	// subf r31,r31,r29
	ctx.r31.u64 = ctx.r29.u64 - ctx.r31.u64;
	// subf r27,r27,r3
	ctx.r27.u64 = ctx.r3.u64 - ctx.r27.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// srawi r25,r25,8
	ctx.xer.ca = (ctx.r25.s32 < 0) & ((ctx.r25.u32 & 0xFF) != 0);
	ctx.r25.s64 = ctx.r25.s32 >> 8;
	// srawi r23,r30,8
	ctx.xer.ca = (ctx.r30.s32 < 0) & ((ctx.r30.u32 & 0xFF) != 0);
	ctx.r23.s64 = ctx.r30.s32 >> 8;
	// mulli r31,r31,362
	ctx.r31.s64 = static_cast<int64_t>(ctx.r31.u64 * static_cast<uint64_t>(362));
	// mulli r30,r28,277
	ctx.r30.s64 = static_cast<int64_t>(ctx.r28.u64 * static_cast<uint64_t>(277));
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// srawi r22,r31,8
	ctx.xer.ca = (ctx.r31.s32 < 0) & ((ctx.r31.u32 & 0xFF) != 0);
	ctx.r22.s64 = ctx.r31.s32 >> 8;
	// srawi r21,r30,8
	ctx.xer.ca = (ctx.r30.s32 < 0) & ((ctx.r30.u32 & 0xFF) != 0);
	ctx.r21.s64 = ctx.r30.s32 >> 8;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// extsh r31,r27
	ctx.r31.s64 = ctx.r27.s16;
	// extsh r30,r26
	ctx.r30.s64 = ctx.r26.s16;
	// subf r28,r5,r23
	ctx.r28.u64 = ctx.r23.u64 - ctx.r5.u64;
	// extsh r29,r25
	ctx.r29.s64 = ctx.r25.s16;
	// add r27,r5,r4
	ctx.r27.u64 = ctx.r5.u64 + ctx.r4.u64;
	// subf r4,r5,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r5.u64;
	// add r5,r28,r29
	ctx.r5.u64 = ctx.r28.u64 + ctx.r29.u64;
	// subf r29,r29,r21
	ctx.r29.u64 = ctx.r21.u64 - ctx.r29.u64;
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// stw r27,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r27.u32);
	// add r28,r5,r3
	ctx.r28.u64 = ctx.r5.u64 + ctx.r3.u64;
	// stw r4,224(r11)
	REX_STORE_U32(ctx.r11.u32 + 224, ctx.r4.u32);
	// subf r3,r5,r3
	ctx.r3.u64 = ctx.r3.u64 - ctx.r5.u64;
	// subf r4,r5,r22
	ctx.r4.u64 = ctx.r22.u64 - ctx.r5.u64;
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// stw r28,32(r11)
	REX_STORE_U32(ctx.r11.u32 + 32, ctx.r28.u32);
	// stw r3,192(r11)
	REX_STORE_U32(ctx.r11.u32 + 192, ctx.r3.u32);
	// add r3,r5,r31
	ctx.r3.u64 = ctx.r5.u64 + ctx.r31.u64;
	// add r4,r29,r5
	ctx.r4.u64 = ctx.r29.u64 + ctx.r5.u64;
	// subf r5,r5,r31
	ctx.r5.u64 = ctx.r31.u64 - ctx.r5.u64;
	// stw r3,64(r11)
	REX_STORE_U32(ctx.r11.u32 + 64, ctx.r3.u32);
	// stw r5,160(r11)
	REX_STORE_U32(ctx.r11.u32 + 160, ctx.r5.u32);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// add r4,r5,r30
	ctx.r4.u64 = ctx.r5.u64 + ctx.r30.u64;
	// subf r3,r5,r30
	ctx.r3.u64 = ctx.r30.u64 - ctx.r5.u64;
	// stw r4,128(r11)
	REX_STORE_U32(ctx.r11.u32 + 128, ctx.r4.u32);
	// stw r3,96(r11)
	REX_STORE_U32(ctx.r11.u32 + 96, ctx.r3.u32);
loc_92247828:
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// addi r10,r10,2
	ctx.r10.s64 = ctx.r10.s64 + 2;
	// addi r8,r8,2
	ctx.r8.s64 = ctx.r8.s64 + 2;
	// cmpwi cr6,r24,0
	ctx.cr6.compare<int32_t>(ctx.r24.s32, 0, ctx.xer);
	// bgt cr6,0x922475f0
	if (ctx.cr6.gt) goto loc_922475F0;
	// addi r10,r1,-368
	ctx.r10.s64 = ctx.r1.s64 + -368;
	// mr r26,r6
	ctx.r26.u64 = ctx.r6.u64;
	// li r25,8
	ctx.r25.s64 = 8;
loc_9224784C:
	// lwz r6,8(r10)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r10.u32 + 8);
	// lwz r5,4(r10)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r10.u32 + 4);
	// lwz r4,12(r10)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r10.u32 + 12);
	// or r8,r5,r6
	ctx.r8.u64 = ctx.r5.u64 | ctx.r6.u64;
	// lwz r3,16(r10)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r10.u32 + 16);
	// lwz r31,20(r10)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r10.u32 + 20);
	// or r8,r8,r4
	ctx.r8.u64 = ctx.r8.u64 | ctx.r4.u64;
	// lwz r30,24(r10)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r10.u32 + 24);
	// lwz r29,28(r10)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r10.u32 + 28);
	// or r8,r8,r3
	ctx.r8.u64 = ctx.r8.u64 | ctx.r3.u64;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// or r8,r8,r31
	ctx.r8.u64 = ctx.r8.u64 | ctx.r31.u64;
	// add r11,r11,r7
	ctx.r11.u64 = ctx.r11.u64 + ctx.r7.u64;
	// or r8,r8,r30
	ctx.r8.u64 = ctx.r8.u64 | ctx.r30.u64;
	// or r8,r8,r29
	ctx.r8.u64 = ctx.r8.u64 | ctx.r29.u64;
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne cr6,0x922478c4
	if (!ctx.cr6.eq) goto loc_922478C4;
	// lwz r6,0(r10)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r10.u32 + 0);
	// srawi r5,r6,5
	ctx.xer.ca = (ctx.r6.s32 < 0) & ((ctx.r6.u32 & 0x1F) != 0);
	ctx.r5.s64 = ctx.r6.s32 >> 5;
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r8,r4,r9
	ctx.r8.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r8,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r8.u8);
	// stb r8,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r8.u8);
	// stb r8,2(r11)
	REX_STORE_U8(ctx.r11.u32 + 2, ctx.r8.u8);
	// stb r8,3(r11)
	REX_STORE_U8(ctx.r11.u32 + 3, ctx.r8.u8);
	// stb r8,4(r11)
	REX_STORE_U8(ctx.r11.u32 + 4, ctx.r8.u8);
	// stb r8,5(r11)
	REX_STORE_U8(ctx.r11.u32 + 5, ctx.r8.u8);
	// stb r8,6(r11)
	REX_STORE_U8(ctx.r11.u32 + 6, ctx.r8.u8);
	// stb r8,7(r11)
	REX_STORE_U8(ctx.r11.u32 + 7, ctx.r8.u8);
	// b 0x92247a40
	goto loc_92247A40;
loc_922478C4:
	// subf r27,r29,r5
	ctx.r27.u64 = ctx.r5.u64 - ctx.r29.u64;
	// lwz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r10.u32 + 0);
	// subf r28,r4,r31
	ctx.r28.u64 = ctx.r31.u64 - ctx.r4.u64;
	// add r29,r5,r29
	ctx.r29.u64 = ctx.r5.u64 + ctx.r29.u64;
	// add r31,r4,r31
	ctx.r31.u64 = ctx.r4.u64 + ctx.r31.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mr r5,r27
	ctx.r5.u64 = ctx.r27.u64;
	// extsh r28,r6
	ctx.r28.s64 = ctx.r6.s16;
	// extsh r27,r30
	ctx.r27.s64 = ctx.r30.s16;
	// add r30,r6,r30
	ctx.r30.u64 = ctx.r6.u64 + ctx.r30.u64;
	// subf r28,r27,r28
	ctx.r28.u64 = ctx.r28.u64 - ctx.r27.u64;
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// mulli r6,r28,362
	ctx.r6.s64 = static_cast<int64_t>(ctx.r28.u64 * static_cast<uint64_t>(362));
	// add r28,r8,r3
	ctx.r28.u64 = ctx.r8.u64 + ctx.r3.u64;
	// srawi r24,r6,8
	ctx.xer.ca = (ctx.r6.s32 < 0) & ((ctx.r6.u32 & 0xFF) != 0);
	ctx.r24.s64 = ctx.r6.s32 >> 8;
	// extsh r6,r4
	ctx.r6.s64 = ctx.r4.s16;
	// extsh r4,r31
	ctx.r4.s64 = ctx.r31.s16;
	// extsh r31,r28
	ctx.r31.s64 = ctx.r28.s16;
	// mulli r28,r6,-669
	ctx.r28.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(-669));
	// add r6,r6,r5
	ctx.r6.u64 = ctx.r6.u64 + ctx.r5.u64;
	// subf r27,r3,r8
	ctx.r27.u64 = ctx.r8.u64 - ctx.r3.u64;
	// extsh r3,r29
	ctx.r3.s64 = ctx.r29.s16;
	// mulli r6,r6,473
	ctx.r6.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(473));
	// extsh r8,r30
	ctx.r8.s64 = ctx.r30.s16;
	// add r30,r4,r3
	ctx.r30.u64 = ctx.r4.u64 + ctx.r3.u64;
	// subf r4,r4,r3
	ctx.r4.u64 = ctx.r3.u64 - ctx.r4.u64;
	// srawi r29,r6,8
	ctx.xer.ca = (ctx.r6.s32 < 0) & ((ctx.r6.u32 & 0xFF) != 0);
	ctx.r29.s64 = ctx.r6.s32 >> 8;
	// subf r6,r8,r24
	ctx.r6.u64 = ctx.r24.u64 - ctx.r8.u64;
	// mulli r3,r5,277
	ctx.r3.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(277));
	// mulli r5,r4,362
	ctx.r5.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(362));
	// srawi r24,r28,8
	ctx.xer.ca = (ctx.r28.s32 < 0) & ((ctx.r28.u32 & 0xFF) != 0);
	ctx.r24.s64 = ctx.r28.s32 >> 8;
	// mr r28,r6
	ctx.r28.u64 = ctx.r6.u64;
	// extsh r6,r27
	ctx.r6.s64 = ctx.r27.s16;
	// srawi r27,r5,8
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0xFF) != 0);
	ctx.r27.s64 = ctx.r5.s32 >> 8;
	// srawi r23,r3,8
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0xFF) != 0);
	ctx.r23.s64 = ctx.r3.s32 >> 8;
	// add r3,r31,r8
	ctx.r3.u64 = ctx.r31.u64 + ctx.r8.u64;
	// subf r31,r8,r31
	ctx.r31.u64 = ctx.r31.u64 - ctx.r8.u64;
	// extsh r8,r30
	ctx.r8.s64 = ctx.r30.s16;
	// extsh r5,r29
	ctx.r5.s64 = ctx.r29.s16;
	// subf r29,r8,r24
	ctx.r29.u64 = ctx.r24.u64 - ctx.r8.u64;
	// extsh r4,r28
	ctx.r4.s64 = ctx.r28.s16;
	// subf r30,r5,r23
	ctx.r30.u64 = ctx.r23.u64 - ctx.r5.u64;
	// add r5,r29,r5
	ctx.r5.u64 = ctx.r29.u64 + ctx.r5.u64;
	// add r29,r6,r4
	ctx.r29.u64 = ctx.r6.u64 + ctx.r4.u64;
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// subf r4,r4,r6
	ctx.r4.u64 = ctx.r6.u64 - ctx.r4.u64;
	// mr r6,r29
	ctx.r6.u64 = ctx.r29.u64;
	// add r29,r8,r3
	ctx.r29.u64 = ctx.r8.u64 + ctx.r3.u64;
	// subf r3,r8,r3
	ctx.r3.u64 = ctx.r3.u64 - ctx.r8.u64;
	// srawi r8,r29,5
	ctx.xer.ca = (ctx.r29.s32 < 0) & ((ctx.r29.u32 & 0x1F) != 0);
	ctx.r8.s64 = ctx.r29.s32 >> 5;
	// srawi r3,r3,5
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x1F) != 0);
	ctx.r3.s64 = ctx.r3.s32 >> 5;
	// clrlwi r8,r8,22
	ctx.r8.u64 = ctx.r8.u32 & 0x3FF;
	// clrlwi r3,r3,22
	ctx.r3.u64 = ctx.r3.u32 & 0x3FF;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// lbzx r8,r8,r9
	ctx.r8.u64 = REX_LOAD_U8(ctx.r8.u32 + ctx.r9.u32);
	// stb r8,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r8.u8);
	// extsh r8,r5
	ctx.r8.s64 = ctx.r5.s16;
	// lbzx r3,r3,r9
	ctx.r3.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r9.u32);
	// extsh r5,r6
	ctx.r5.s64 = ctx.r6.s16;
	// subf r6,r8,r27
	ctx.r6.u64 = ctx.r27.u64 - ctx.r8.u64;
	// extsh r6,r6
	ctx.r6.s64 = ctx.r6.s16;
	// stb r3,7(r11)
	REX_STORE_U8(ctx.r11.u32 + 7, ctx.r3.u8);
	// add r3,r8,r5
	ctx.r3.u64 = ctx.r8.u64 + ctx.r5.u64;
	// subf r8,r8,r5
	ctx.r8.u64 = ctx.r5.u64 - ctx.r8.u64;
	// srawi r3,r3,5
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x1F) != 0);
	ctx.r3.s64 = ctx.r3.s32 >> 5;
	// srawi r5,r8,5
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0x1F) != 0);
	ctx.r5.s64 = ctx.r8.s32 >> 5;
	// clrlwi r3,r3,22
	ctx.r3.u64 = ctx.r3.u32 & 0x3FF;
	// clrlwi r8,r5,22
	ctx.r8.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r29,r3,r9
	ctx.r29.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r9.u32);
	// add r3,r30,r6
	ctx.r3.u64 = ctx.r30.u64 + ctx.r6.u64;
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// stb r29,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r29.u8);
	// lbzx r5,r8,r9
	ctx.r5.u64 = REX_LOAD_U8(ctx.r8.u32 + ctx.r9.u32);
	// add r8,r6,r4
	ctx.r8.u64 = ctx.r6.u64 + ctx.r4.u64;
	// subf r6,r6,r4
	ctx.r6.u64 = ctx.r4.u64 - ctx.r6.u64;
	// stb r5,6(r11)
	REX_STORE_U8(ctx.r11.u32 + 6, ctx.r5.u8);
	// srawi r5,r8,5
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0x1F) != 0);
	ctx.r5.s64 = ctx.r8.s32 >> 5;
	// srawi r4,r6,5
	ctx.xer.ca = (ctx.r6.s32 < 0) & ((ctx.r6.u32 & 0x1F) != 0);
	ctx.r4.s64 = ctx.r6.s32 >> 5;
	// clrlwi r8,r5,22
	ctx.r8.u64 = ctx.r5.u32 & 0x3FF;
	// clrlwi r6,r4,22
	ctx.r6.u64 = ctx.r4.u32 & 0x3FF;
	// lbzx r8,r8,r9
	ctx.r8.u64 = REX_LOAD_U8(ctx.r8.u32 + ctx.r9.u32);
	// add r5,r3,r31
	ctx.r5.u64 = ctx.r3.u64 + ctx.r31.u64;
	// subf r4,r3,r31
	ctx.r4.u64 = ctx.r31.u64 - ctx.r3.u64;
	// srawi r3,r5,5
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x1F) != 0);
	ctx.r3.s64 = ctx.r5.s32 >> 5;
	// srawi r5,r4,5
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1F) != 0);
	ctx.r5.s64 = ctx.r4.s32 >> 5;
	// clrlwi r4,r3,22
	ctx.r4.u64 = ctx.r3.u32 & 0x3FF;
	// stb r8,2(r11)
	REX_STORE_U8(ctx.r11.u32 + 2, ctx.r8.u8);
	// clrlwi r3,r5,22
	ctx.r3.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r8,r6,r9
	ctx.r8.u64 = REX_LOAD_U8(ctx.r6.u32 + ctx.r9.u32);
	// stb r8,5(r11)
	REX_STORE_U8(ctx.r11.u32 + 5, ctx.r8.u8);
	// lbzx r6,r4,r9
	ctx.r6.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r9.u32);
	// stb r6,4(r11)
	REX_STORE_U8(ctx.r11.u32 + 4, ctx.r6.u8);
	// lbzx r5,r3,r9
	ctx.r5.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r9.u32);
	// stb r5,3(r11)
	REX_STORE_U8(ctx.r11.u32 + 3, ctx.r5.u8);
loc_92247A40:
	// addi r25,r25,-1
	ctx.r25.s64 = ctx.r25.s64 + -1;
	// addi r10,r10,32
	ctx.r10.s64 = ctx.r10.s64 + 32;
	// addi r26,r26,4
	ctx.r26.s64 = ctx.r26.s64 + 4;
	// cmplwi cr6,r25,0
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 0, ctx.xer);
	// bne cr6,0x9224784c
	if (!ctx.cr6.eq) goto loc_9224784C;
	// b 0x9205b4a4
	__restgprlr_19(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92247A58) {
	REX_FUNC_PROLOGUE();
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b44c
	ctx.lr = 0x92247A60;
	__savegprlr_17(ctx, base);
	// lwz r8,328(r3)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// mr r9,r5
	ctx.r9.u64 = ctx.r5.u64;
	// lwz r10,80(r4)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// addi r11,r1,-384
	ctx.r11.s64 = ctx.r1.s64 + -384;
	// addi r8,r8,128
	ctx.r8.s64 = ctx.r8.s64 + 128;
	// li r20,8
	ctx.r20.s64 = 8;
loc_92247A78:
	// lhz r5,16(r9)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r9.u32 + 16);
	// extsh r26,r5
	ctx.r26.s64 = ctx.r5.s16;
	// cmpwi cr6,r26,0
	ctx.cr6.compare<int32_t>(ctx.r26.s32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r4,32(r9)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r9.u32 + 32);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r3,48(r9)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r9.u32 + 48);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r5,64(r9)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r9.u32 + 64);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r4,80(r9)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r9.u32 + 80);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r3,96(r9)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r9.u32 + 96);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r5,112(r9)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r9.u32 + 112);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x92247b08
	if (!ctx.cr6.eq) goto loc_92247B08;
	// lhz r4,0(r9)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r9.u32 + 0);
	// lhz r3,0(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// extsh r4,r3
	ctx.r4.s64 = ctx.r3.s16;
	// mullw r3,r5,r4
	ctx.r3.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// rlwinm r5,r3,2,0,29
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r3.u32 | (ctx.r3.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r5,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r5.u32);
	// stw r5,32(r11)
	REX_STORE_U32(ctx.r11.u32 + 32, ctx.r5.u32);
	// stw r5,64(r11)
	REX_STORE_U32(ctx.r11.u32 + 64, ctx.r5.u32);
	// stw r5,96(r11)
	REX_STORE_U32(ctx.r11.u32 + 96, ctx.r5.u32);
	// stw r5,160(r11)
	REX_STORE_U32(ctx.r11.u32 + 160, ctx.r5.u32);
	// stw r5,192(r11)
	REX_STORE_U32(ctx.r11.u32 + 192, ctx.r5.u32);
	// stw r5,224(r11)
	REX_STORE_U32(ctx.r11.u32 + 224, ctx.r5.u32);
	// b 0x92247cb4
	goto loc_92247CB4;
loc_92247B08:
	// lhz r5,32(r10)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r10.u32 + 32);
	// lhz r4,32(r9)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r9.u32 + 32);
	// lhz r3,96(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 96);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// lhz r31,96(r9)
	ctx.r31.u64 = REX_LOAD_U16(ctx.r9.u32 + 96);
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// lhz r29,0(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// lhz r28,64(r10)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r10.u32 + 64);
	// mullw r5,r5,r4
	ctx.r5.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// lhz r30,0(r9)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r9.u32 + 0);
	// lhz r27,64(r9)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r9.u32 + 64);
	// lhz r23,80(r10)
	ctx.r23.u64 = REX_LOAD_U16(ctx.r10.u32 + 80);
	// lhz r22,80(r9)
	ctx.r22.u64 = REX_LOAD_U16(ctx.r9.u32 + 80);
	// lhz r21,48(r10)
	ctx.r21.u64 = REX_LOAD_U16(ctx.r10.u32 + 48);
	// lhz r19,48(r9)
	ctx.r19.u64 = REX_LOAD_U16(ctx.r9.u32 + 48);
	// lhz r25,112(r10)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r10.u32 + 112);
	// lhz r24,112(r9)
	ctx.r24.u64 = REX_LOAD_U16(ctx.r9.u32 + 112);
	// lhz r18,16(r10)
	ctx.r18.u64 = REX_LOAD_U16(ctx.r10.u32 + 16);
	// mullw r4,r3,r31
	ctx.r4.s64 = int64_t(ctx.r3.s32) * int64_t(ctx.r31.s32);
	// extsh r31,r29
	ctx.r31.s64 = ctx.r29.s16;
	// extsh r29,r28
	ctx.r29.s64 = ctx.r28.s16;
	// extsh r3,r30
	ctx.r3.s64 = ctx.r30.s16;
	// extsh r28,r27
	ctx.r28.s64 = ctx.r27.s16;
	// add r27,r4,r5
	ctx.r27.u64 = ctx.r4.u64 + ctx.r5.u64;
	// mulli r17,r4,15137
	ctx.r17.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(15137));
	// mulli r30,r5,6270
	ctx.r30.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(6270));
	// mullw r5,r3,r31
	ctx.r5.s64 = int64_t(ctx.r3.s32) * int64_t(ctx.r31.s32);
	// mullw r4,r29,r28
	ctx.r4.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r28.s32);
	// add r31,r4,r5
	ctx.r31.u64 = ctx.r4.u64 + ctx.r5.u64;
	// mulli r3,r27,4433
	ctx.r3.s64 = static_cast<int64_t>(ctx.r27.u64 * static_cast<uint64_t>(4433));
	// subf r4,r4,r5
	ctx.r4.u64 = ctx.r5.u64 - ctx.r4.u64;
	// rlwinm r5,r31,13,0,18
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 13) & 0xFFFFE000;
	// subf r31,r17,r3
	ctx.r31.u64 = ctx.r3.u64 - ctx.r17.u64;
	// add r3,r30,r3
	ctx.r3.u64 = ctx.r30.u64 + ctx.r3.u64;
	// rlwinm r4,r4,13,0,18
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 13) & 0xFFFFE000;
	// extsh r23,r23
	ctx.r23.s64 = ctx.r23.s16;
	// extsh r22,r22
	ctx.r22.s64 = ctx.r22.s16;
	// extsh r21,r21
	ctx.r21.s64 = ctx.r21.s16;
	// extsh r19,r19
	ctx.r19.s64 = ctx.r19.s16;
	// extsh r25,r25
	ctx.r25.s64 = ctx.r25.s16;
	// extsh r24,r24
	ctx.r24.s64 = ctx.r24.s16;
	// extsh r18,r18
	ctx.r18.s64 = ctx.r18.s16;
	// add r29,r5,r3
	ctx.r29.u64 = ctx.r5.u64 + ctx.r3.u64;
	// add r30,r4,r31
	ctx.r30.u64 = ctx.r4.u64 + ctx.r31.u64;
	// subf r27,r31,r4
	ctx.r27.u64 = ctx.r4.u64 - ctx.r31.u64;
	// subf r28,r3,r5
	ctx.r28.u64 = ctx.r5.u64 - ctx.r3.u64;
	// mullw r3,r21,r19
	ctx.r3.s64 = int64_t(ctx.r21.s32) * int64_t(ctx.r19.s32);
	// mullw r4,r23,r22
	ctx.r4.s64 = int64_t(ctx.r23.s32) * int64_t(ctx.r22.s32);
	// mullw r31,r18,r26
	ctx.r31.s64 = int64_t(ctx.r18.s32) * int64_t(ctx.r26.s32);
	// mullw r5,r25,r24
	ctx.r5.s64 = int64_t(ctx.r25.s32) * int64_t(ctx.r24.s32);
	// add r25,r4,r3
	ctx.r25.u64 = ctx.r4.u64 + ctx.r3.u64;
	// mulli r23,r4,16819
	ctx.r23.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(16819));
	// add r26,r5,r3
	ctx.r26.u64 = ctx.r5.u64 + ctx.r3.u64;
	// add r4,r4,r31
	ctx.r4.u64 = ctx.r4.u64 + ctx.r31.u64;
	// mulli r24,r3,25172
	ctx.r24.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(25172));
	// add r3,r5,r31
	ctx.r3.u64 = ctx.r5.u64 + ctx.r31.u64;
	// mulli r22,r31,12299
	ctx.r22.s64 = static_cast<int64_t>(ctx.r31.u64 * static_cast<uint64_t>(12299));
	// add r31,r4,r26
	ctx.r31.u64 = ctx.r4.u64 + ctx.r26.u64;
	// mulli r19,r26,16069
	ctx.r19.s64 = static_cast<int64_t>(ctx.r26.u64 * static_cast<uint64_t>(16069));
	// mulli r26,r4,3196
	ctx.r26.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(3196));
	// mulli r4,r31,9633
	ctx.r4.s64 = static_cast<int64_t>(ctx.r31.u64 * static_cast<uint64_t>(9633));
	// subf r31,r26,r4
	ctx.r31.u64 = ctx.r4.u64 - ctx.r26.u64;
	// mulli r3,r3,-7373
	ctx.r3.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(-7373));
	// mulli r21,r5,2446
	ctx.r21.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(2446));
	// add r26,r22,r31
	ctx.r26.u64 = ctx.r22.u64 + ctx.r31.u64;
	// mulli r5,r25,-20995
	ctx.r5.s64 = static_cast<int64_t>(ctx.r25.u64 * static_cast<uint64_t>(-20995));
	// subf r4,r19,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r19.u64;
	// add r25,r21,r3
	ctx.r25.u64 = ctx.r21.u64 + ctx.r3.u64;
	// add r3,r26,r3
	ctx.r3.u64 = ctx.r26.u64 + ctx.r3.u64;
	// add r31,r23,r31
	ctx.r31.u64 = ctx.r23.u64 + ctx.r31.u64;
	// add r26,r24,r4
	ctx.r26.u64 = ctx.r24.u64 + ctx.r4.u64;
	// add r4,r25,r4
	ctx.r4.u64 = ctx.r25.u64 + ctx.r4.u64;
	// add r25,r29,r3
	ctx.r25.u64 = ctx.r29.u64 + ctx.r3.u64;
	// add r31,r31,r5
	ctx.r31.u64 = ctx.r31.u64 + ctx.r5.u64;
	// add r5,r26,r5
	ctx.r5.u64 = ctx.r26.u64 + ctx.r5.u64;
	// subf r26,r3,r29
	ctx.r26.u64 = ctx.r29.u64 - ctx.r3.u64;
	// addi r3,r25,1024
	ctx.r3.s64 = ctx.r25.s64 + 1024;
	// srawi r3,r3,11
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7FF) != 0);
	ctx.r3.s64 = ctx.r3.s32 >> 11;
	// stw r3,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r3.u32);
	// subf r3,r5,r30
	ctx.r3.u64 = ctx.r30.u64 - ctx.r5.u64;
	// add r29,r30,r5
	ctx.r29.u64 = ctx.r30.u64 + ctx.r5.u64;
	// add r5,r27,r31
	ctx.r5.u64 = ctx.r27.u64 + ctx.r31.u64;
	// addi r30,r26,1024
	ctx.r30.s64 = ctx.r26.s64 + 1024;
	// addi r29,r29,1024
	ctx.r29.s64 = ctx.r29.s64 + 1024;
	// subf r31,r31,r27
	ctx.r31.u64 = ctx.r27.u64 - ctx.r31.u64;
	// addi r27,r3,1024
	ctx.r27.s64 = ctx.r3.s64 + 1024;
	// addi r26,r5,1024
	ctx.r26.s64 = ctx.r5.s64 + 1024;
	// add r3,r28,r4
	ctx.r3.u64 = ctx.r28.u64 + ctx.r4.u64;
	// srawi r30,r30,11
	ctx.xer.ca = (ctx.r30.s32 < 0) & ((ctx.r30.u32 & 0x7FF) != 0);
	ctx.r30.s64 = ctx.r30.s32 >> 11;
	// subf r5,r4,r28
	ctx.r5.u64 = ctx.r28.u64 - ctx.r4.u64;
	// srawi r4,r29,11
	ctx.xer.ca = (ctx.r29.s32 < 0) & ((ctx.r29.u32 & 0x7FF) != 0);
	ctx.r4.s64 = ctx.r29.s32 >> 11;
	// addi r31,r31,1024
	ctx.r31.s64 = ctx.r31.s64 + 1024;
	// srawi r29,r27,11
	ctx.xer.ca = (ctx.r27.s32 < 0) & ((ctx.r27.u32 & 0x7FF) != 0);
	ctx.r29.s64 = ctx.r27.s32 >> 11;
	// stw r30,224(r11)
	REX_STORE_U32(ctx.r11.u32 + 224, ctx.r30.u32);
	// addi r3,r3,1024
	ctx.r3.s64 = ctx.r3.s64 + 1024;
	// srawi r30,r26,11
	ctx.xer.ca = (ctx.r26.s32 < 0) & ((ctx.r26.u32 & 0x7FF) != 0);
	ctx.r30.s64 = ctx.r26.s32 >> 11;
	// stw r4,32(r11)
	REX_STORE_U32(ctx.r11.u32 + 32, ctx.r4.u32);
	// srawi r4,r31,11
	ctx.xer.ca = (ctx.r31.s32 < 0) & ((ctx.r31.u32 & 0x7FF) != 0);
	ctx.r4.s64 = ctx.r31.s32 >> 11;
	// srawi r3,r3,11
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7FF) != 0);
	ctx.r3.s64 = ctx.r3.s32 >> 11;
	// addi r5,r5,1024
	ctx.r5.s64 = ctx.r5.s64 + 1024;
	// stw r29,192(r11)
	REX_STORE_U32(ctx.r11.u32 + 192, ctx.r29.u32);
	// srawi r5,r5,11
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x7FF) != 0);
	ctx.r5.s64 = ctx.r5.s32 >> 11;
	// stw r30,64(r11)
	REX_STORE_U32(ctx.r11.u32 + 64, ctx.r30.u32);
	// stw r4,160(r11)
	REX_STORE_U32(ctx.r11.u32 + 160, ctx.r4.u32);
	// stw r3,96(r11)
	REX_STORE_U32(ctx.r11.u32 + 96, ctx.r3.u32);
loc_92247CB4:
	// addi r20,r20,-1
	ctx.r20.s64 = ctx.r20.s64 + -1;
	// stw r5,128(r11)
	REX_STORE_U32(ctx.r11.u32 + 128, ctx.r5.u32);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// addi r10,r10,2
	ctx.r10.s64 = ctx.r10.s64 + 2;
	// addi r9,r9,2
	ctx.r9.s64 = ctx.r9.s64 + 2;
	// cmpwi cr6,r20,0
	ctx.cr6.compare<int32_t>(ctx.r20.s32, 0, ctx.xer);
	// bgt cr6,0x92247a78
	if (ctx.cr6.gt) goto loc_92247A78;
	// addi r11,r1,-384
	ctx.r11.s64 = ctx.r1.s64 + -384;
	// mr r19,r6
	ctx.r19.u64 = ctx.r6.u64;
	// li r18,8
	ctx.r18.s64 = 8;
	// lis r9,2
	ctx.r9.s64 = 131072;
loc_92247CE0:
	// lwz r3,4(r11)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r11.u32 + 4);
	// lwz r10,0(r19)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r19.u32 + 0);
	// cmpwi cr6,r3,0
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// add r10,r10,r7
	ctx.r10.u64 = ctx.r10.u64 + ctx.r7.u64;
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r4,8(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 8);
	// cmpwi cr6,r4,0
	ctx.cr6.compare<int32_t>(ctx.r4.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r6,12(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 12);
	// cmpwi cr6,r6,0
	ctx.cr6.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r5,16(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 16);
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r4,20(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 20);
	// cmpwi cr6,r4,0
	ctx.cr6.compare<int32_t>(ctx.r4.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r6,24(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 24);
	// cmpwi cr6,r6,0
	ctx.cr6.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r5,28(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 28);
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x92247d70
	if (!ctx.cr6.eq) goto loc_92247D70;
	// lwz r6,0(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r4,r6,16
	ctx.r4.s64 = ctx.r6.s64 + 16;
	// srawi r3,r4,5
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1F) != 0);
	ctx.r3.s64 = ctx.r4.s32 >> 5;
	// clrlwi r6,r3,22
	ctx.r6.u64 = ctx.r3.u32 & 0x3FF;
	// lbzx r6,r6,r8
	ctx.r6.u64 = REX_LOAD_U8(ctx.r6.u32 + ctx.r8.u32);
	// stb r6,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r6.u8);
	// stb r6,1(r10)
	REX_STORE_U8(ctx.r10.u32 + 1, ctx.r6.u8);
	// stb r6,2(r10)
	REX_STORE_U8(ctx.r10.u32 + 2, ctx.r6.u8);
	// stb r6,3(r10)
	REX_STORE_U8(ctx.r10.u32 + 3, ctx.r6.u8);
	// stb r6,5(r10)
	REX_STORE_U8(ctx.r10.u32 + 5, ctx.r6.u8);
	// stb r6,6(r10)
	REX_STORE_U8(ctx.r10.u32 + 6, ctx.r6.u8);
	// stb r6,7(r10)
	REX_STORE_U8(ctx.r10.u32 + 7, ctx.r6.u8);
	// b 0x92247ee0
	goto loc_92247EE0;
loc_92247D70:
	// lwz r6,8(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 8);
	// mulli r21,r3,12299
	ctx.r21.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(12299));
	// lwz r5,24(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 24);
	// mulli r30,r6,6270
	ctx.r30.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(6270));
	// lwz r31,0(r11)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// lwz r4,16(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 16);
	// add r6,r5,r6
	ctx.r6.u64 = ctx.r5.u64 + ctx.r6.u64;
	// mulli r29,r5,15137
	ctx.r29.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(15137));
	// add r5,r31,r4
	ctx.r5.u64 = ctx.r31.u64 + ctx.r4.u64;
	// subf r4,r4,r31
	ctx.r4.u64 = ctx.r31.u64 - ctx.r4.u64;
	// mulli r6,r6,4433
	ctx.r6.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(4433));
	// rlwinm r5,r5,13,0,18
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r5.u32 | (ctx.r5.u64 << 32), 13) & 0xFFFFE000;
	// subf r31,r29,r6
	ctx.r31.u64 = ctx.r6.u64 - ctx.r29.u64;
	// rlwinm r4,r4,13,0,18
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 13) & 0xFFFFE000;
	// add r30,r30,r6
	ctx.r30.u64 = ctx.r30.u64 + ctx.r6.u64;
	// add r29,r4,r31
	ctx.r29.u64 = ctx.r4.u64 + ctx.r31.u64;
	// lwz r6,20(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 20);
	// add r28,r5,r30
	ctx.r28.u64 = ctx.r5.u64 + ctx.r30.u64;
	// subf r30,r30,r5
	ctx.r30.u64 = ctx.r5.u64 - ctx.r30.u64;
	// subf r31,r31,r4
	ctx.r31.u64 = ctx.r4.u64 - ctx.r31.u64;
	// lwz r5,12(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 12);
	// lwz r4,28(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 28);
	// add r26,r6,r3
	ctx.r26.u64 = ctx.r6.u64 + ctx.r3.u64;
	// add r27,r4,r5
	ctx.r27.u64 = ctx.r4.u64 + ctx.r5.u64;
	// add r25,r4,r3
	ctx.r25.u64 = ctx.r4.u64 + ctx.r3.u64;
	// add r3,r26,r27
	ctx.r3.u64 = ctx.r26.u64 + ctx.r27.u64;
	// add r24,r6,r5
	ctx.r24.u64 = ctx.r6.u64 + ctx.r5.u64;
	// mulli r17,r27,16069
	ctx.r17.s64 = static_cast<int64_t>(ctx.r27.u64 * static_cast<uint64_t>(16069));
	// mulli r23,r6,16819
	ctx.r23.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(16819));
	// mulli r6,r3,9633
	ctx.r6.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(9633));
	// mulli r27,r26,3196
	ctx.r27.s64 = static_cast<int64_t>(ctx.r26.u64 * static_cast<uint64_t>(3196));
	// subf r3,r27,r6
	ctx.r3.u64 = ctx.r6.u64 - ctx.r27.u64;
	// mulli r22,r5,25172
	ctx.r22.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(25172));
	// subf r6,r17,r6
	ctx.r6.u64 = ctx.r6.u64 - ctx.r17.u64;
	// mulli r20,r4,2446
	ctx.r20.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(2446));
	// mulli r5,r25,-7373
	ctx.r5.s64 = static_cast<int64_t>(ctx.r25.u64 * static_cast<uint64_t>(-7373));
	// add r25,r21,r3
	ctx.r25.u64 = ctx.r21.u64 + ctx.r3.u64;
	// mulli r4,r24,-20995
	ctx.r4.s64 = static_cast<int64_t>(ctx.r24.u64 * static_cast<uint64_t>(-20995));
	// add r27,r22,r6
	ctx.r27.u64 = ctx.r22.u64 + ctx.r6.u64;
	// add r26,r20,r5
	ctx.r26.u64 = ctx.r20.u64 + ctx.r5.u64;
	// add r3,r23,r3
	ctx.r3.u64 = ctx.r23.u64 + ctx.r3.u64;
	// add r5,r25,r5
	ctx.r5.u64 = ctx.r25.u64 + ctx.r5.u64;
	// add r27,r27,r4
	ctx.r27.u64 = ctx.r27.u64 + ctx.r4.u64;
	// add r4,r3,r4
	ctx.r4.u64 = ctx.r3.u64 + ctx.r4.u64;
	// add r3,r28,r5
	ctx.r3.u64 = ctx.r28.u64 + ctx.r5.u64;
	// subf r5,r5,r28
	ctx.r5.u64 = ctx.r28.u64 - ctx.r5.u64;
	// add r3,r3,r9
	ctx.r3.u64 = ctx.r3.u64 + ctx.r9.u64;
	// add r5,r5,r9
	ctx.r5.u64 = ctx.r5.u64 + ctx.r9.u64;
	// srawi r3,r3,18
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x3FFFF) != 0);
	ctx.r3.s64 = ctx.r3.s32 >> 18;
	// srawi r5,r5,18
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x3FFFF) != 0);
	ctx.r5.s64 = ctx.r5.s32 >> 18;
	// clrlwi r3,r3,22
	ctx.r3.u64 = ctx.r3.u32 & 0x3FF;
	// add r28,r29,r27
	ctx.r28.u64 = ctx.r29.u64 + ctx.r27.u64;
	// clrlwi r5,r5,22
	ctx.r5.u64 = ctx.r5.u32 & 0x3FF;
	// add r28,r28,r9
	ctx.r28.u64 = ctx.r28.u64 + ctx.r9.u64;
	// subf r29,r27,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r27.u64;
	// srawi r28,r28,18
	ctx.xer.ca = (ctx.r28.s32 < 0) & ((ctx.r28.u32 & 0x3FFFF) != 0);
	ctx.r28.s64 = ctx.r28.s32 >> 18;
	// lbzx r3,r3,r8
	ctx.r3.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r8.u32);
	// add r29,r29,r9
	ctx.r29.u64 = ctx.r29.u64 + ctx.r9.u64;
	// clrlwi r28,r28,22
	ctx.r28.u64 = ctx.r28.u32 & 0x3FF;
	// srawi r29,r29,18
	ctx.xer.ca = (ctx.r29.s32 < 0) & ((ctx.r29.u32 & 0x3FFFF) != 0);
	ctx.r29.s64 = ctx.r29.s32 >> 18;
	// add r27,r31,r4
	ctx.r27.u64 = ctx.r31.u64 + ctx.r4.u64;
	// subf r4,r4,r31
	ctx.r4.u64 = ctx.r31.u64 - ctx.r4.u64;
	// stb r3,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r3.u8);
	// clrlwi r3,r29,22
	ctx.r3.u64 = ctx.r29.u32 & 0x3FF;
	// lbzx r5,r5,r8
	ctx.r5.u64 = REX_LOAD_U8(ctx.r5.u32 + ctx.r8.u32);
	// add r29,r27,r9
	ctx.r29.u64 = ctx.r27.u64 + ctx.r9.u64;
	// add r6,r26,r6
	ctx.r6.u64 = ctx.r26.u64 + ctx.r6.u64;
	// srawi r29,r29,18
	ctx.xer.ca = (ctx.r29.s32 < 0) & ((ctx.r29.u32 & 0x3FFFF) != 0);
	ctx.r29.s64 = ctx.r29.s32 >> 18;
	// stb r5,7(r10)
	REX_STORE_U8(ctx.r10.u32 + 7, ctx.r5.u8);
	// clrlwi r29,r29,22
	ctx.r29.u64 = ctx.r29.u32 & 0x3FF;
	// lbzx r5,r28,r8
	ctx.r5.u64 = REX_LOAD_U8(ctx.r28.u32 + ctx.r8.u32);
	// stb r5,1(r10)
	REX_STORE_U8(ctx.r10.u32 + 1, ctx.r5.u8);
	// lbzx r3,r3,r8
	ctx.r3.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r8.u32);
	// stb r3,6(r10)
	REX_STORE_U8(ctx.r10.u32 + 6, ctx.r3.u8);
	// add r3,r30,r6
	ctx.r3.u64 = ctx.r30.u64 + ctx.r6.u64;
	// lbzx r5,r29,r8
	ctx.r5.u64 = REX_LOAD_U8(ctx.r29.u32 + ctx.r8.u32);
	// add r3,r3,r9
	ctx.r3.u64 = ctx.r3.u64 + ctx.r9.u64;
	// stb r5,2(r10)
	REX_STORE_U8(ctx.r10.u32 + 2, ctx.r5.u8);
	// add r5,r4,r9
	ctx.r5.u64 = ctx.r4.u64 + ctx.r9.u64;
	// srawi r4,r5,18
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x3FFFF) != 0);
	ctx.r4.s64 = ctx.r5.s32 >> 18;
	// clrlwi r5,r4,22
	ctx.r5.u64 = ctx.r4.u32 & 0x3FF;
	// srawi r4,r3,18
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x3FFFF) != 0);
	ctx.r4.s64 = ctx.r3.s32 >> 18;
	// lbzx r5,r5,r8
	ctx.r5.u64 = REX_LOAD_U8(ctx.r5.u32 + ctx.r8.u32);
	// subf r3,r6,r30
	ctx.r3.u64 = ctx.r30.u64 - ctx.r6.u64;
	// clrlwi r6,r4,22
	ctx.r6.u64 = ctx.r4.u32 & 0x3FF;
	// add r4,r3,r9
	ctx.r4.u64 = ctx.r3.u64 + ctx.r9.u64;
	// srawi r3,r4,18
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x3FFFF) != 0);
	ctx.r3.s64 = ctx.r4.s32 >> 18;
	// stb r5,5(r10)
	REX_STORE_U8(ctx.r10.u32 + 5, ctx.r5.u8);
	// clrlwi r4,r3,22
	ctx.r4.u64 = ctx.r3.u32 & 0x3FF;
	// lbzx r3,r6,r8
	ctx.r3.u64 = REX_LOAD_U8(ctx.r6.u32 + ctx.r8.u32);
	// stb r3,3(r10)
	REX_STORE_U8(ctx.r10.u32 + 3, ctx.r3.u8);
	// lbzx r6,r4,r8
	ctx.r6.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r8.u32);
loc_92247EE0:
	// addi r18,r18,-1
	ctx.r18.s64 = ctx.r18.s64 + -1;
	// stb r6,4(r10)
	REX_STORE_U8(ctx.r10.u32 + 4, ctx.r6.u8);
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// addi r19,r19,4
	ctx.r19.s64 = ctx.r19.s64 + 4;
	// cmplwi cr6,r18,0
	ctx.cr6.compare<uint32_t>(ctx.r18.u32, 0, ctx.xer);
	// bne cr6,0x92247ce0
	if (!ctx.cr6.eq) goto loc_92247CE0;
	// b 0x9205b49c
	__restgprlr_17(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92247F00) {
	REX_FUNC_PROLOGUE();
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b458
	ctx.lr = 0x92247F08;
	__savegprlr_20(ctx, base);
	// lwz r11,80(r4)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// li r26,8
	ctx.r26.s64 = 8;
	// lwz r8,328(r3)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// addi r9,r1,-208
	ctx.r9.s64 = ctx.r1.s64 + -208;
	// addi r10,r5,96
	ctx.r10.s64 = ctx.r5.s64 + 96;
	// addi r27,r8,128
	ctx.r27.s64 = ctx.r8.s64 + 128;
	// addi r11,r11,96
	ctx.r11.s64 = ctx.r11.s64 + 96;
loc_92247F24:
	// cmpwi cr6,r26,4
	ctx.cr6.compare<int32_t>(ctx.r26.s32, 4, ctx.xer);
	// beq cr6,0x922480b4
	if (ctx.cr6.eq) goto loc_922480B4;
	// lhz r8,-80(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -80);
	// extsh r5,r8
	ctx.r5.s64 = ctx.r8.s16;
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r4,-64(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + -64);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r3,-48(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + -48);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r8,-16(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -16);
	// cmplwi cr6,r8,0
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r4,0(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r3,16(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 16);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x92247fa0
	if (!ctx.cr6.eq) goto loc_92247FA0;
	// lhz r8,-96(r11)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r11.u32 + -96);
	// lhz r5,-96(r10)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r10.u32 + -96);
	// extsh r4,r8
	ctx.r4.s64 = ctx.r8.s16;
	// extsh r3,r5
	ctx.r3.s64 = ctx.r5.s16;
	// mullw r8,r4,r3
	ctx.r8.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r3.s32);
	// rlwinm r8,r8,2,0,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r8,-32(r9)
	REX_STORE_U32(ctx.r9.u32 + -32, ctx.r8.u32);
	// stw r8,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r8.u32);
	// stw r8,64(r9)
	REX_STORE_U32(ctx.r9.u32 + 64, ctx.r8.u32);
	// b 0x922480b0
	goto loc_922480B0;
loc_92247FA0:
	// lhz r8,-80(r11)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r11.u32 + -80);
	// lhz r4,-48(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -48);
	// extsh r29,r8
	ctx.r29.s64 = ctx.r8.s16;
	// lhz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// lhz r3,-48(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + -48);
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r24,r8
	ctx.r24.s64 = ctx.r8.s16;
	// lhz r8,-16(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -16);
	// lhz r25,-16(r11)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r11.u32 + -16);
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// lhz r31,-64(r11)
	ctx.r31.u64 = REX_LOAD_U16(ctx.r11.u32 + -64);
	// extsh r21,r8
	ctx.r21.s64 = ctx.r8.s16;
	// lhz r30,-64(r10)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r10.u32 + -64);
	// extsh r25,r25
	ctx.r25.s64 = ctx.r25.s16;
	// lhz r28,0(r11)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r11.u32 + 0);
	// mullw r8,r4,r3
	ctx.r8.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r3.s32);
	// lhz r23,-96(r11)
	ctx.r23.u64 = REX_LOAD_U16(ctx.r11.u32 + -96);
	// lhz r22,-96(r10)
	ctx.r22.u64 = REX_LOAD_U16(ctx.r10.u32 + -96);
	// lhz r20,16(r11)
	ctx.r20.u64 = REX_LOAD_U16(ctx.r11.u32 + 16);
	// lhz r3,16(r10)
	ctx.r3.u64 = REX_LOAD_U16(ctx.r10.u32 + 16);
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// extsh r31,r31
	ctx.r31.s64 = ctx.r31.s16;
	// mullw r5,r29,r5
	ctx.r5.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r5.s32);
	// mullw r4,r25,r21
	ctx.r4.s64 = int64_t(ctx.r25.s32) * int64_t(ctx.r21.s32);
	// extsh r28,r28
	ctx.r28.s64 = ctx.r28.s16;
	// extsh r25,r22
	ctx.r25.s64 = ctx.r22.s16;
	// extsh r29,r23
	ctx.r29.s64 = ctx.r23.s16;
	// mullw r31,r31,r30
	ctx.r31.s64 = int64_t(ctx.r31.s32) * int64_t(ctx.r30.s32);
	// mullw r30,r24,r28
	ctx.r30.s64 = int64_t(ctx.r24.s32) * int64_t(ctx.r28.s32);
	// mullw r29,r29,r25
	ctx.r29.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r25.s32);
	// extsh r3,r3
	ctx.r3.s64 = ctx.r3.s16;
	// extsh r28,r20
	ctx.r28.s64 = ctx.r20.s16;
	// mulli r25,r31,15137
	ctx.r25.s64 = static_cast<int64_t>(ctx.r31.u64 * static_cast<uint64_t>(15137));
	// mulli r30,r30,6270
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(6270));
	// mullw r3,r28,r3
	ctx.r3.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r3.s32);
	// rlwinm r31,r29,14,0,17
	ctx.r31.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 14) & 0xFFFFC000;
	// mulli r28,r8,7373
	ctx.r28.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(7373));
	// mulli r29,r5,20995
	ctx.r29.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(20995));
	// subf r30,r30,r25
	ctx.r30.u64 = ctx.r25.u64 - ctx.r30.u64;
	// mulli r25,r4,11893
	ctx.r25.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(11893));
	// mulli r8,r8,17799
	ctx.r8.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(17799));
	// mulli r24,r4,4926
	ctx.r24.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(4926));
	// add r28,r29,r28
	ctx.r28.u64 = ctx.r29.u64 + ctx.r28.u64;
	// subf r4,r8,r25
	ctx.r4.u64 = ctx.r25.u64 - ctx.r8.u64;
	// mulli r29,r5,8697
	ctx.r29.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(8697));
	// mulli r25,r3,4176
	ctx.r25.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(4176));
	// subf r28,r24,r28
	ctx.r28.u64 = ctx.r28.u64 - ctx.r24.u64;
	// subf r5,r30,r31
	ctx.r5.u64 = ctx.r31.u64 - ctx.r30.u64;
	// add r8,r30,r31
	ctx.r8.u64 = ctx.r30.u64 + ctx.r31.u64;
	// add r31,r4,r29
	ctx.r31.u64 = ctx.r4.u64 + ctx.r29.u64;
	// mulli r3,r3,1730
	ctx.r3.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(1730));
	// subf r4,r25,r28
	ctx.r4.u64 = ctx.r28.u64 - ctx.r25.u64;
	// subf r3,r3,r31
	ctx.r3.u64 = ctx.r31.u64 - ctx.r3.u64;
	// add r30,r8,r4
	ctx.r30.u64 = ctx.r8.u64 + ctx.r4.u64;
	// subf r31,r4,r8
	ctx.r31.u64 = ctx.r8.u64 - ctx.r4.u64;
	// add r4,r5,r3
	ctx.r4.u64 = ctx.r5.u64 + ctx.r3.u64;
	// subf r8,r3,r5
	ctx.r8.u64 = ctx.r5.u64 - ctx.r3.u64;
	// addi r30,r30,2048
	ctx.r30.s64 = ctx.r30.s64 + 2048;
	// addi r5,r31,2048
	ctx.r5.s64 = ctx.r31.s64 + 2048;
	// addi r4,r4,2048
	ctx.r4.s64 = ctx.r4.s64 + 2048;
	// srawi r3,r30,12
	ctx.xer.ca = (ctx.r30.s32 < 0) & ((ctx.r30.u32 & 0xFFF) != 0);
	ctx.r3.s64 = ctx.r30.s32 >> 12;
	// srawi r5,r5,12
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0xFFF) != 0);
	ctx.r5.s64 = ctx.r5.s32 >> 12;
	// srawi r4,r4,12
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0xFFF) != 0);
	ctx.r4.s64 = ctx.r4.s32 >> 12;
	// addi r8,r8,2048
	ctx.r8.s64 = ctx.r8.s64 + 2048;
	// srawi r8,r8,12
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0xFFF) != 0);
	ctx.r8.s64 = ctx.r8.s32 >> 12;
	// stw r3,-32(r9)
	REX_STORE_U32(ctx.r9.u32 + -32, ctx.r3.u32);
	// stw r5,64(r9)
	REX_STORE_U32(ctx.r9.u32 + 64, ctx.r5.u32);
	// stw r4,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r4.u32);
loc_922480B0:
	// stw r8,32(r9)
	REX_STORE_U32(ctx.r9.u32 + 32, ctx.r8.u32);
loc_922480B4:
	// addi r26,r26,-1
	ctx.r26.s64 = ctx.r26.s64 + -1;
	// addi r10,r10,2
	ctx.r10.s64 = ctx.r10.s64 + 2;
	// addi r11,r11,2
	ctx.r11.s64 = ctx.r11.s64 + 2;
	// addi r9,r9,4
	ctx.r9.s64 = ctx.r9.s64 + 4;
	// cmpwi cr6,r26,0
	ctx.cr6.compare<int32_t>(ctx.r26.s32, 0, ctx.xer);
	// bgt cr6,0x92247f24
	if (ctx.cr6.gt) goto loc_92247F24;
	// addi r11,r1,-240
	ctx.r11.s64 = ctx.r1.s64 + -240;
	// mr r28,r6
	ctx.r28.u64 = ctx.r6.u64;
	// li r26,4
	ctx.r26.s64 = 4;
	// lis r31,4
	ctx.r31.s64 = 262144;
loc_922480DC:
	// lwz r30,4(r11)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r11.u32 + 4);
	// lwz r10,0(r28)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// cmpwi cr6,r30,0
	ctx.cr6.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// add r10,r10,r7
	ctx.r10.u64 = ctx.r10.u64 + ctx.r7.u64;
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r6,8(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 8);
	// cmpwi cr6,r6,0
	ctx.cr6.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r5,12(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 12);
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r4,20(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 20);
	// cmpwi cr6,r4,0
	ctx.cr6.compare<int32_t>(ctx.r4.s32, 0, ctx.xer);
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r3,24(r11)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r11.u32 + 24);
	// cmpwi cr6,r3,0
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r9,28(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 28);
	// cmpwi cr6,r9,0
	ctx.cr6.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// bne cr6,0x92248158
	if (!ctx.cr6.eq) goto loc_92248158;
	// lwz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// addi r8,r9,16
	ctx.r8.s64 = ctx.r9.s64 + 16;
	// srawi r6,r8,5
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0x1F) != 0);
	ctx.r6.s64 = ctx.r8.s32 >> 5;
	// clrlwi r5,r6,22
	ctx.r5.u64 = ctx.r6.u32 & 0x3FF;
	// lbzx r9,r5,r27
	ctx.r9.u64 = REX_LOAD_U8(ctx.r5.u32 + ctx.r27.u32);
	// stb r9,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r9.u8);
	// stb r9,1(r10)
	REX_STORE_U8(ctx.r10.u32 + 1, ctx.r9.u8);
	// stb r9,2(r10)
	REX_STORE_U8(ctx.r10.u32 + 2, ctx.r9.u8);
	// stb r9,3(r10)
	REX_STORE_U8(ctx.r10.u32 + 3, ctx.r9.u8);
	// b 0x92248224
	goto loc_92248224;
loc_92248158:
	// lwz r4,8(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 8);
	// lwz r3,24(r11)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r11.u32 + 24);
	// mulli r4,r4,15137
	ctx.r4.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(15137));
	// lwz r9,12(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 12);
	// mulli r3,r3,6270
	ctx.r3.s64 = static_cast<int64_t>(ctx.r3.u64 * static_cast<uint64_t>(6270));
	// lwz r8,20(r11)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r11.u32 + 20);
	// lwz r5,0(r11)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// lwz r6,28(r11)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r11.u32 + 28);
	// subf r4,r3,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r3.u64;
	// mulli r29,r9,7373
	ctx.r29.s64 = static_cast<int64_t>(ctx.r9.u64 * static_cast<uint64_t>(7373));
	// mulli r3,r30,20995
	ctx.r3.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(20995));
	// add r3,r3,r29
	ctx.r3.u64 = ctx.r3.u64 + ctx.r29.u64;
	// mulli r29,r8,4926
	ctx.r29.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(4926));
	// mulli r8,r8,11893
	ctx.r8.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(11893));
	// mulli r9,r9,17799
	ctx.r9.s64 = static_cast<int64_t>(ctx.r9.u64 * static_cast<uint64_t>(17799));
	// rlwinm r5,r5,14,0,17
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r5.u32 | (ctx.r5.u64 << 32), 14) & 0xFFFFC000;
	// subf r9,r9,r8
	ctx.r9.u64 = ctx.r8.u64 - ctx.r9.u64;
	// subf r29,r29,r3
	ctx.r29.u64 = ctx.r3.u64 - ctx.r29.u64;
	// mulli r25,r6,4176
	ctx.r25.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(4176));
	// add r3,r4,r5
	ctx.r3.u64 = ctx.r4.u64 + ctx.r5.u64;
	// mulli r8,r30,8697
	ctx.r8.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(8697));
	// subf r5,r4,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r4.u64;
	// subf r4,r25,r29
	ctx.r4.u64 = ctx.r29.u64 - ctx.r25.u64;
	// add r9,r9,r8
	ctx.r9.u64 = ctx.r9.u64 + ctx.r8.u64;
	// mulli r8,r6,1730
	ctx.r8.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(1730));
	// add r6,r3,r4
	ctx.r6.u64 = ctx.r3.u64 + ctx.r4.u64;
	// subf r4,r4,r3
	ctx.r4.u64 = ctx.r3.u64 - ctx.r4.u64;
	// add r3,r6,r31
	ctx.r3.u64 = ctx.r6.u64 + ctx.r31.u64;
	// subf r9,r8,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r8.u64;
	// srawi r6,r3,19
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7FFFF) != 0);
	ctx.r6.s64 = ctx.r3.s32 >> 19;
	// add r8,r4,r31
	ctx.r8.u64 = ctx.r4.u64 + ctx.r31.u64;
	// clrlwi r3,r6,22
	ctx.r3.u64 = ctx.r6.u32 & 0x3FF;
	// srawi r4,r8,19
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0x7FFFF) != 0);
	ctx.r4.s64 = ctx.r8.s32 >> 19;
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// clrlwi r8,r4,22
	ctx.r8.u64 = ctx.r4.u32 & 0x3FF;
	// lbzx r6,r3,r27
	ctx.r6.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r27.u32);
	// add r3,r5,r9
	ctx.r3.u64 = ctx.r5.u64 + ctx.r9.u64;
	// subf r9,r9,r5
	ctx.r9.u64 = ctx.r5.u64 - ctx.r9.u64;
	// stb r6,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r6.u8);
	// add r6,r9,r31
	ctx.r6.u64 = ctx.r9.u64 + ctx.r31.u64;
	// lbzx r4,r8,r27
	ctx.r4.u64 = REX_LOAD_U8(ctx.r8.u32 + ctx.r27.u32);
	// add r8,r3,r31
	ctx.r8.u64 = ctx.r3.u64 + ctx.r31.u64;
	// srawi r5,r8,19
	ctx.xer.ca = (ctx.r8.s32 < 0) & ((ctx.r8.u32 & 0x7FFFF) != 0);
	ctx.r5.s64 = ctx.r8.s32 >> 19;
	// clrlwi r3,r5,22
	ctx.r3.u64 = ctx.r5.u32 & 0x3FF;
	// stb r4,3(r10)
	REX_STORE_U8(ctx.r10.u32 + 3, ctx.r4.u8);
	// srawi r4,r6,19
	ctx.xer.ca = (ctx.r6.s32 < 0) & ((ctx.r6.u32 & 0x7FFFF) != 0);
	ctx.r4.s64 = ctx.r6.s32 >> 19;
	// clrlwi r9,r4,22
	ctx.r9.u64 = ctx.r4.u32 & 0x3FF;
	// lbzx r8,r3,r27
	ctx.r8.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r27.u32);
	// stb r8,1(r10)
	REX_STORE_U8(ctx.r10.u32 + 1, ctx.r8.u8);
	// lbzx r6,r9,r27
	ctx.r6.u64 = REX_LOAD_U8(ctx.r9.u32 + ctx.r27.u32);
	// stb r6,2(r10)
	REX_STORE_U8(ctx.r10.u32 + 2, ctx.r6.u8);
loc_92248224:
	// addi r26,r26,-1
	ctx.r26.s64 = ctx.r26.s64 + -1;
	// addi r28,r28,4
	ctx.r28.s64 = ctx.r28.s64 + 4;
	// cmplwi cr6,r26,0
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 0, ctx.xer);
	// bne cr6,0x922480dc
	if (!ctx.cr6.eq) goto loc_922480DC;
	// b 0x9205b4a8
	__restgprlr_20(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92248238) {
	REX_FUNC_PROLOGUE();
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b46c
	ctx.lr = 0x92248240;
	__savegprlr_25(ctx, base);
	// lwz r10,80(r4)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// li r31,6
	ctx.r31.s64 = 6;
	// lwz r8,328(r3)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// addi r9,r1,-124
	ctx.r9.s64 = ctx.r1.s64 + -124;
	// addi r11,r5,48
	ctx.r11.s64 = ctx.r5.s64 + 48;
	// addi r3,r8,128
	ctx.r3.s64 = ctx.r8.s64 + 128;
	// addi r10,r10,48
	ctx.r10.s64 = ctx.r10.s64 + 48;
loc_9224825C:
	// addi r8,r31,2
	ctx.r8.s64 = ctx.r31.s64 + 2;
	// cmpwi cr6,r8,6
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 6, ctx.xer);
	// beq cr6,0x92248368
	if (ctx.cr6.eq) goto loc_92248368;
	// cmpwi cr6,r8,4
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 4, ctx.xer);
	// beq cr6,0x92248368
	if (ctx.cr6.eq) goto loc_92248368;
	// cmpwi cr6,r8,2
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 2, ctx.xer);
	// beq cr6,0x92248368
	if (ctx.cr6.eq) goto loc_92248368;
	// lhz r8,-32(r11)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r11.u32 + -32);
	// extsh r8,r8
	ctx.r8.s64 = ctx.r8.s16;
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne cr6,0x922482cc
	if (!ctx.cr6.eq) goto loc_922482CC;
	// lhz r5,0(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 0);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922482cc
	if (!ctx.cr6.eq) goto loc_922482CC;
	// lhz r4,32(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + 32);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x922482cc
	if (!ctx.cr6.eq) goto loc_922482CC;
	// lhz r5,64(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 64);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922482cc
	if (!ctx.cr6.eq) goto loc_922482CC;
	// lhz r4,-48(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -48);
	// lhz r8,-48(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -48);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// extsh r4,r8
	ctx.r4.s64 = ctx.r8.s16;
	// mullw r8,r5,r4
	ctx.r8.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// rlwinm r8,r8,2,0,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r8,28(r9)
	REX_STORE_U32(ctx.r9.u32 + 28, ctx.r8.u32);
	// b 0x92248364
	goto loc_92248364;
loc_922482CC:
	// lhz r30,64(r11)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r11.u32 + 64);
	// lhz r29,64(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 64);
	// lhz r5,32(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 32);
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// lhz r4,32(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 32);
	// extsh r29,r29
	ctx.r29.s64 = ctx.r29.s16;
	// lhz r28,0(r10)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r10.u32 + 0);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// lhz r27,0(r11)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r11.u32 + 0);
	// mullw r30,r30,r29
	ctx.r30.s64 = int64_t(ctx.r30.s32) * int64_t(ctx.r29.s32);
	// lhz r26,-32(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + -32);
	// lhz r25,-48(r10)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r10.u32 + -48);
	// extsh r29,r28
	ctx.r29.s64 = ctx.r28.s16;
	// mullw r5,r5,r4
	ctx.r5.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// lhz r4,-48(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -48);
	// extsh r28,r27
	ctx.r28.s64 = ctx.r27.s16;
	// mulli r5,r5,6967
	ctx.r5.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(6967));
	// mullw r29,r29,r28
	ctx.r29.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r28.s32);
	// mulli r30,r30,5906
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(5906));
	// extsh r28,r26
	ctx.r28.s64 = ctx.r26.s16;
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r27,r25
	ctx.r27.s64 = ctx.r25.s16;
	// mullw r8,r28,r8
	ctx.r8.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r8.s32);
	// mulli r30,r29,10426
	ctx.r30.s64 = static_cast<int64_t>(ctx.r29.u64 * static_cast<uint64_t>(10426));
	// mullw r29,r4,r27
	ctx.r29.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r27.s32);
	// mulli r4,r8,29692
	ctx.r4.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(29692));
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// rlwinm r8,r29,15,0,16
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 15) & 0xFFFF8000;
	// add r5,r5,r4
	ctx.r5.u64 = ctx.r5.u64 + ctx.r4.u64;
	// add r4,r5,r8
	ctx.r4.u64 = ctx.r5.u64 + ctx.r8.u64;
	// subf r8,r5,r8
	ctx.r8.u64 = ctx.r8.u64 - ctx.r5.u64;
	// addi r5,r4,4096
	ctx.r5.s64 = ctx.r4.s64 + 4096;
	// addi r4,r8,4096
	ctx.r4.s64 = ctx.r8.s64 + 4096;
	// srawi r8,r5,13
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x1FFF) != 0);
	ctx.r8.s64 = ctx.r5.s32 >> 13;
	// srawi r5,r4,13
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1FFF) != 0);
	ctx.r5.s64 = ctx.r4.s32 >> 13;
	// stw r5,28(r9)
	REX_STORE_U32(ctx.r9.u32 + 28, ctx.r5.u32);
loc_92248364:
	// stw r8,-4(r9)
	REX_STORE_U32(ctx.r9.u32 + -4, ctx.r8.u32);
loc_92248368:
	// addi r8,r31,1
	ctx.r8.s64 = ctx.r31.s64 + 1;
	// cmpwi cr6,r8,6
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 6, ctx.xer);
	// beq cr6,0x92248474
	if (ctx.cr6.eq) goto loc_92248474;
	// cmpwi cr6,r8,4
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 4, ctx.xer);
	// beq cr6,0x92248474
	if (ctx.cr6.eq) goto loc_92248474;
	// cmpwi cr6,r8,2
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 2, ctx.xer);
	// beq cr6,0x92248474
	if (ctx.cr6.eq) goto loc_92248474;
	// lhz r4,-30(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -30);
	// extsh r8,r4
	ctx.r8.s64 = ctx.r4.s16;
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne cr6,0x922483d8
	if (!ctx.cr6.eq) goto loc_922483D8;
	// lhz r5,2(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 2);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922483d8
	if (!ctx.cr6.eq) goto loc_922483D8;
	// lhz r4,34(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + 34);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x922483d8
	if (!ctx.cr6.eq) goto loc_922483D8;
	// lhz r5,66(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 66);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922483d8
	if (!ctx.cr6.eq) goto loc_922483D8;
	// lhz r4,-46(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -46);
	// lhz r8,-46(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -46);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// extsh r4,r8
	ctx.r4.s64 = ctx.r8.s16;
	// mullw r8,r5,r4
	ctx.r8.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// rlwinm r8,r8,2,0,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r8,32(r9)
	REX_STORE_U32(ctx.r9.u32 + 32, ctx.r8.u32);
	// b 0x92248470
	goto loc_92248470;
loc_922483D8:
	// lhz r30,66(r11)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r11.u32 + 66);
	// lhz r29,66(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 66);
	// lhz r5,34(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 34);
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// lhz r4,34(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 34);
	// extsh r29,r29
	ctx.r29.s64 = ctx.r29.s16;
	// lhz r28,2(r11)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r11.u32 + 2);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// lhz r27,2(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 2);
	// mullw r30,r30,r29
	ctx.r30.s64 = int64_t(ctx.r30.s32) * int64_t(ctx.r29.s32);
	// lhz r26,-30(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + -30);
	// lhz r25,-46(r10)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r10.u32 + -46);
	// extsh r29,r28
	ctx.r29.s64 = ctx.r28.s16;
	// mullw r5,r5,r4
	ctx.r5.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// lhz r4,-46(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -46);
	// extsh r28,r27
	ctx.r28.s64 = ctx.r27.s16;
	// mulli r5,r5,6967
	ctx.r5.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(6967));
	// mullw r29,r29,r28
	ctx.r29.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r28.s32);
	// mulli r30,r30,5906
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(5906));
	// extsh r28,r26
	ctx.r28.s64 = ctx.r26.s16;
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r27,r25
	ctx.r27.s64 = ctx.r25.s16;
	// mullw r8,r28,r8
	ctx.r8.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r8.s32);
	// mulli r30,r29,10426
	ctx.r30.s64 = static_cast<int64_t>(ctx.r29.u64 * static_cast<uint64_t>(10426));
	// mullw r29,r4,r27
	ctx.r29.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r27.s32);
	// mulli r4,r8,29692
	ctx.r4.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(29692));
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// rlwinm r8,r29,15,0,16
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 15) & 0xFFFF8000;
	// add r5,r5,r4
	ctx.r5.u64 = ctx.r5.u64 + ctx.r4.u64;
	// add r4,r5,r8
	ctx.r4.u64 = ctx.r5.u64 + ctx.r8.u64;
	// subf r8,r5,r8
	ctx.r8.u64 = ctx.r8.u64 - ctx.r5.u64;
	// addi r5,r4,4096
	ctx.r5.s64 = ctx.r4.s64 + 4096;
	// addi r4,r8,4096
	ctx.r4.s64 = ctx.r8.s64 + 4096;
	// srawi r8,r5,13
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x1FFF) != 0);
	ctx.r8.s64 = ctx.r5.s32 >> 13;
	// srawi r5,r4,13
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1FFF) != 0);
	ctx.r5.s64 = ctx.r4.s32 >> 13;
	// stw r5,32(r9)
	REX_STORE_U32(ctx.r9.u32 + 32, ctx.r5.u32);
loc_92248470:
	// stw r8,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r8.u32);
loc_92248474:
	// cmpwi cr6,r31,6
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 6, ctx.xer);
	// beq cr6,0x9224857c
	if (ctx.cr6.eq) goto loc_9224857C;
	// cmpwi cr6,r31,4
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 4, ctx.xer);
	// beq cr6,0x9224857c
	if (ctx.cr6.eq) goto loc_9224857C;
	// cmpwi cr6,r31,2
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 2, ctx.xer);
	// beq cr6,0x9224857c
	if (ctx.cr6.eq) goto loc_9224857C;
	// lhz r4,-28(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -28);
	// extsh r8,r4
	ctx.r8.s64 = ctx.r4.s16;
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne cr6,0x922484e0
	if (!ctx.cr6.eq) goto loc_922484E0;
	// lhz r5,4(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 4);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922484e0
	if (!ctx.cr6.eq) goto loc_922484E0;
	// lhz r4,36(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + 36);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x922484e0
	if (!ctx.cr6.eq) goto loc_922484E0;
	// lhz r5,68(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 68);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922484e0
	if (!ctx.cr6.eq) goto loc_922484E0;
	// lhz r4,-44(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -44);
	// lhz r8,-44(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -44);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// extsh r4,r8
	ctx.r4.s64 = ctx.r8.s16;
	// mullw r8,r5,r4
	ctx.r8.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// rlwinm r8,r8,2,0,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r8,36(r9)
	REX_STORE_U32(ctx.r9.u32 + 36, ctx.r8.u32);
	// b 0x92248578
	goto loc_92248578;
loc_922484E0:
	// lhz r30,68(r11)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r11.u32 + 68);
	// lhz r29,68(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 68);
	// lhz r5,36(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 36);
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// lhz r4,36(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 36);
	// extsh r29,r29
	ctx.r29.s64 = ctx.r29.s16;
	// lhz r28,4(r11)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r11.u32 + 4);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// lhz r27,4(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 4);
	// mullw r30,r30,r29
	ctx.r30.s64 = int64_t(ctx.r30.s32) * int64_t(ctx.r29.s32);
	// lhz r26,-28(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + -28);
	// lhz r25,-44(r10)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r10.u32 + -44);
	// extsh r29,r28
	ctx.r29.s64 = ctx.r28.s16;
	// mullw r5,r5,r4
	ctx.r5.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// lhz r4,-44(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -44);
	// extsh r28,r27
	ctx.r28.s64 = ctx.r27.s16;
	// mulli r5,r5,6967
	ctx.r5.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(6967));
	// mullw r29,r29,r28
	ctx.r29.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r28.s32);
	// mulli r30,r30,5906
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(5906));
	// extsh r28,r26
	ctx.r28.s64 = ctx.r26.s16;
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r27,r25
	ctx.r27.s64 = ctx.r25.s16;
	// mullw r8,r28,r8
	ctx.r8.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r8.s32);
	// mulli r30,r29,10426
	ctx.r30.s64 = static_cast<int64_t>(ctx.r29.u64 * static_cast<uint64_t>(10426));
	// mullw r29,r4,r27
	ctx.r29.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r27.s32);
	// mulli r4,r8,29692
	ctx.r4.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(29692));
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// rlwinm r8,r29,15,0,16
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 15) & 0xFFFF8000;
	// add r5,r5,r4
	ctx.r5.u64 = ctx.r5.u64 + ctx.r4.u64;
	// add r4,r5,r8
	ctx.r4.u64 = ctx.r5.u64 + ctx.r8.u64;
	// subf r8,r5,r8
	ctx.r8.u64 = ctx.r8.u64 - ctx.r5.u64;
	// addi r5,r4,4096
	ctx.r5.s64 = ctx.r4.s64 + 4096;
	// addi r4,r8,4096
	ctx.r4.s64 = ctx.r8.s64 + 4096;
	// srawi r8,r5,13
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x1FFF) != 0);
	ctx.r8.s64 = ctx.r5.s32 >> 13;
	// srawi r5,r4,13
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1FFF) != 0);
	ctx.r5.s64 = ctx.r4.s32 >> 13;
	// stw r5,36(r9)
	REX_STORE_U32(ctx.r9.u32 + 36, ctx.r5.u32);
loc_92248578:
	// stw r8,4(r9)
	REX_STORE_U32(ctx.r9.u32 + 4, ctx.r8.u32);
loc_9224857C:
	// addi r8,r31,-1
	ctx.r8.s64 = ctx.r31.s64 + -1;
	// cmpwi cr6,r8,6
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 6, ctx.xer);
	// beq cr6,0x92248688
	if (ctx.cr6.eq) goto loc_92248688;
	// cmpwi cr6,r8,4
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 4, ctx.xer);
	// beq cr6,0x92248688
	if (ctx.cr6.eq) goto loc_92248688;
	// cmpwi cr6,r8,2
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 2, ctx.xer);
	// beq cr6,0x92248688
	if (ctx.cr6.eq) goto loc_92248688;
	// lhz r4,-26(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -26);
	// extsh r8,r4
	ctx.r8.s64 = ctx.r4.s16;
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne cr6,0x922485ec
	if (!ctx.cr6.eq) goto loc_922485EC;
	// lhz r5,6(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 6);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922485ec
	if (!ctx.cr6.eq) goto loc_922485EC;
	// lhz r4,38(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + 38);
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x922485ec
	if (!ctx.cr6.eq) goto loc_922485EC;
	// lhz r5,70(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 70);
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x922485ec
	if (!ctx.cr6.eq) goto loc_922485EC;
	// lhz r4,-42(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -42);
	// lhz r8,-42(r10)
	ctx.r8.u64 = REX_LOAD_U16(ctx.r10.u32 + -42);
	// extsh r5,r4
	ctx.r5.s64 = ctx.r4.s16;
	// extsh r4,r8
	ctx.r4.s64 = ctx.r8.s16;
	// mullw r8,r5,r4
	ctx.r8.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// rlwinm r8,r8,2,0,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 2) & 0xFFFFFFFC;
	// stw r8,40(r9)
	REX_STORE_U32(ctx.r9.u32 + 40, ctx.r8.u32);
	// b 0x92248684
	goto loc_92248684;
loc_922485EC:
	// lhz r30,70(r11)
	ctx.r30.u64 = REX_LOAD_U16(ctx.r11.u32 + 70);
	// lhz r29,70(r10)
	ctx.r29.u64 = REX_LOAD_U16(ctx.r10.u32 + 70);
	// lhz r5,38(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 38);
	// extsh r30,r30
	ctx.r30.s64 = ctx.r30.s16;
	// lhz r4,38(r10)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r10.u32 + 38);
	// extsh r29,r29
	ctx.r29.s64 = ctx.r29.s16;
	// lhz r28,6(r11)
	ctx.r28.u64 = REX_LOAD_U16(ctx.r11.u32 + 6);
	// extsh r5,r5
	ctx.r5.s64 = ctx.r5.s16;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// lhz r27,6(r10)
	ctx.r27.u64 = REX_LOAD_U16(ctx.r10.u32 + 6);
	// mullw r30,r30,r29
	ctx.r30.s64 = int64_t(ctx.r30.s32) * int64_t(ctx.r29.s32);
	// lhz r26,-26(r10)
	ctx.r26.u64 = REX_LOAD_U16(ctx.r10.u32 + -26);
	// lhz r25,-42(r10)
	ctx.r25.u64 = REX_LOAD_U16(ctx.r10.u32 + -42);
	// extsh r29,r28
	ctx.r29.s64 = ctx.r28.s16;
	// mullw r5,r5,r4
	ctx.r5.s64 = int64_t(ctx.r5.s32) * int64_t(ctx.r4.s32);
	// lhz r4,-42(r11)
	ctx.r4.u64 = REX_LOAD_U16(ctx.r11.u32 + -42);
	// extsh r28,r27
	ctx.r28.s64 = ctx.r27.s16;
	// mulli r5,r5,6967
	ctx.r5.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(6967));
	// mullw r29,r29,r28
	ctx.r29.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r28.s32);
	// mulli r30,r30,5906
	ctx.r30.s64 = static_cast<int64_t>(ctx.r30.u64 * static_cast<uint64_t>(5906));
	// extsh r28,r26
	ctx.r28.s64 = ctx.r26.s16;
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// extsh r4,r4
	ctx.r4.s64 = ctx.r4.s16;
	// extsh r27,r25
	ctx.r27.s64 = ctx.r25.s16;
	// mullw r8,r28,r8
	ctx.r8.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r8.s32);
	// mulli r30,r29,10426
	ctx.r30.s64 = static_cast<int64_t>(ctx.r29.u64 * static_cast<uint64_t>(10426));
	// mullw r29,r4,r27
	ctx.r29.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r27.s32);
	// mulli r4,r8,29692
	ctx.r4.s64 = static_cast<int64_t>(ctx.r8.u64 * static_cast<uint64_t>(29692));
	// subf r5,r30,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r30.u64;
	// rlwinm r8,r29,15,0,16
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 15) & 0xFFFF8000;
	// add r5,r5,r4
	ctx.r5.u64 = ctx.r5.u64 + ctx.r4.u64;
	// add r4,r5,r8
	ctx.r4.u64 = ctx.r5.u64 + ctx.r8.u64;
	// subf r8,r5,r8
	ctx.r8.u64 = ctx.r8.u64 - ctx.r5.u64;
	// addi r5,r4,4096
	ctx.r5.s64 = ctx.r4.s64 + 4096;
	// addi r4,r8,4096
	ctx.r4.s64 = ctx.r8.s64 + 4096;
	// srawi r8,r5,13
	ctx.xer.ca = (ctx.r5.s32 < 0) & ((ctx.r5.u32 & 0x1FFF) != 0);
	ctx.r8.s64 = ctx.r5.s32 >> 13;
	// srawi r5,r4,13
	ctx.xer.ca = (ctx.r4.s32 < 0) & ((ctx.r4.u32 & 0x1FFF) != 0);
	ctx.r5.s64 = ctx.r4.s32 >> 13;
	// stw r5,40(r9)
	REX_STORE_U32(ctx.r9.u32 + 40, ctx.r5.u32);
loc_92248684:
	// stw r8,8(r9)
	REX_STORE_U32(ctx.r9.u32 + 8, ctx.r8.u32);
loc_92248688:
	// addi r31,r31,-4
	ctx.r31.s64 = ctx.r31.s64 + -4;
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// addi r10,r10,8
	ctx.r10.s64 = ctx.r10.s64 + 8;
	// addi r9,r9,16
	ctx.r9.s64 = ctx.r9.s64 + 16;
	// addic. r4,r31,2
	ctx.xer.ca = ctx.r31.u32 > 4294967293;
	ctx.r4.s64 = ctx.r31.s64 + 2;
	ctx.cr0.compare<int32_t>(ctx.r4.s32, 0, ctx.xer);
	// bgt 0x9224825c
	if (ctx.cr0.gt) goto loc_9224825C;
	// lwz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r6.u32 + 0);
	// lis r8,8
	ctx.r8.s64 = 524288;
	// lwz r10,-124(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -124);
	// lwz r5,-100(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + -100);
	// add r11,r11,r7
	ctx.r11.u64 = ctx.r11.u64 + ctx.r7.u64;
	// lwz r9,-108(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + -108);
	// cmpwi cr6,r10,0
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// lwz r4,-116(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + -116);
	// bne cr6,0x922486fc
	if (!ctx.cr6.eq) goto loc_922486FC;
	// cmpwi cr6,r4,0
	ctx.cr6.compare<int32_t>(ctx.r4.s32, 0, ctx.xer);
	// bne cr6,0x922486fc
	if (!ctx.cr6.eq) goto loc_922486FC;
	// cmpwi cr6,r9,0
	ctx.cr6.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// bne cr6,0x922486fc
	if (!ctx.cr6.eq) goto loc_922486FC;
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// bne cr6,0x922486fc
	if (!ctx.cr6.eq) goto loc_922486FC;
	// lwz r10,-128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// addi r9,r10,16
	ctx.r9.s64 = ctx.r10.s64 + 16;
	// srawi r5,r9,5
	ctx.xer.ca = (ctx.r9.s32 < 0) & ((ctx.r9.u32 & 0x1F) != 0);
	ctx.r5.s64 = ctx.r9.s32 >> 5;
	// clrlwi r4,r5,22
	ctx.r4.u64 = ctx.r5.u32 & 0x3FF;
	// lbzx r10,r4,r3
	ctx.r10.u64 = REX_LOAD_U8(ctx.r4.u32 + ctx.r3.u32);
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// stb r10,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r10.u8);
	// b 0x92248750
	goto loc_92248750;
loc_922486FC:
	// mulli r4,r4,10426
	ctx.r4.s64 = static_cast<int64_t>(ctx.r4.u64 * static_cast<uint64_t>(10426));
	// mulli r10,r10,29692
	ctx.r10.s64 = static_cast<int64_t>(ctx.r10.u64 * static_cast<uint64_t>(29692));
	// subf r10,r4,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r4.u64;
	// mulli r9,r9,6967
	ctx.r9.s64 = static_cast<int64_t>(ctx.r9.u64 * static_cast<uint64_t>(6967));
	// lwz r4,-128(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// add r9,r10,r9
	ctx.r9.u64 = ctx.r10.u64 + ctx.r9.u64;
	// mulli r5,r5,5906
	ctx.r5.s64 = static_cast<int64_t>(ctx.r5.u64 * static_cast<uint64_t>(5906));
	// subf r9,r5,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r5.u64;
	// rlwinm r10,r4,15,0,16
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 15) & 0xFFFF8000;
	// add r5,r9,r10
	ctx.r5.u64 = ctx.r9.u64 + ctx.r10.u64;
	// subf r4,r9,r10
	ctx.r4.u64 = ctx.r10.u64 - ctx.r9.u64;
	// add r10,r5,r8
	ctx.r10.u64 = ctx.r5.u64 + ctx.r8.u64;
	// add r9,r4,r8
	ctx.r9.u64 = ctx.r4.u64 + ctx.r8.u64;
	// srawi r5,r10,20
	ctx.xer.ca = (ctx.r10.s32 < 0) & ((ctx.r10.u32 & 0xFFFFF) != 0);
	ctx.r5.s64 = ctx.r10.s32 >> 20;
	// srawi r4,r9,20
	ctx.xer.ca = (ctx.r9.s32 < 0) & ((ctx.r9.u32 & 0xFFFFF) != 0);
	ctx.r4.s64 = ctx.r9.s32 >> 20;
	// clrlwi r10,r5,22
	ctx.r10.u64 = ctx.r5.u32 & 0x3FF;
	// clrlwi r9,r4,22
	ctx.r9.u64 = ctx.r4.u32 & 0x3FF;
	// lbzx r5,r10,r3
	ctx.r5.u64 = REX_LOAD_U8(ctx.r10.u32 + ctx.r3.u32);
	// stb r5,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r5.u8);
	// lbzx r4,r9,r3
	ctx.r4.u64 = REX_LOAD_U8(ctx.r9.u32 + ctx.r3.u32);
	// stb r4,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r4.u8);
loc_92248750:
	// lwz r11,4(r6)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r6.u32 + 4);
	// lwz r9,-92(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + -92);
	// add r11,r11,r7
	ctx.r11.u64 = ctx.r11.u64 + ctx.r7.u64;
	// lwz r10,-76(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -76);
	// lwz r7,-68(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + -68);
	// cmpwi cr6,r9,0
	ctx.cr6.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// lwz r6,-84(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + -84);
	// bne cr6,0x922487a8
	if (!ctx.cr6.eq) goto loc_922487A8;
	// cmpwi cr6,r6,0
	ctx.cr6.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// bne cr6,0x922487a8
	if (!ctx.cr6.eq) goto loc_922487A8;
	// cmpwi cr6,r10,0
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne cr6,0x922487a8
	if (!ctx.cr6.eq) goto loc_922487A8;
	// cmpwi cr6,r7,0
	ctx.cr6.compare<int32_t>(ctx.r7.s32, 0, ctx.xer);
	// bne cr6,0x922487a8
	if (!ctx.cr6.eq) goto loc_922487A8;
	// lwz r10,-96(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -96);
	// addi r9,r10,16
	ctx.r9.s64 = ctx.r10.s64 + 16;
	// srawi r8,r9,5
	ctx.xer.ca = (ctx.r9.s32 < 0) & ((ctx.r9.u32 & 0x1F) != 0);
	ctx.r8.s64 = ctx.r9.s32 >> 5;
	// clrlwi r7,r8,22
	ctx.r7.u64 = ctx.r8.u32 & 0x3FF;
	// lbzx r10,r7,r3
	ctx.r10.u64 = REX_LOAD_U8(ctx.r7.u32 + ctx.r3.u32);
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// stb r10,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r10.u8);
	// b 0x9205b4bc
	__restgprlr_25(ctx, base);
	return;
loc_922487A8:
	// mulli r9,r9,29692
	ctx.r9.s64 = static_cast<int64_t>(ctx.r9.u64 * static_cast<uint64_t>(29692));
	// mulli r10,r10,6967
	ctx.r10.s64 = static_cast<int64_t>(ctx.r10.u64 * static_cast<uint64_t>(6967));
	// add r5,r10,r9
	ctx.r5.u64 = ctx.r10.u64 + ctx.r9.u64;
	// mulli r4,r7,5906
	ctx.r4.s64 = static_cast<int64_t>(ctx.r7.u64 * static_cast<uint64_t>(5906));
	// mulli r7,r6,10426
	ctx.r7.s64 = static_cast<int64_t>(ctx.r6.u64 * static_cast<uint64_t>(10426));
	// lwz r6,-96(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + -96);
	// subf r9,r4,r5
	ctx.r9.u64 = ctx.r5.u64 - ctx.r4.u64;
	// rlwinm r10,r6,15,0,16
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r6.u32 | (ctx.r6.u64 << 32), 15) & 0xFFFF8000;
	// subf r9,r7,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r7.u64;
	// add r5,r9,r10
	ctx.r5.u64 = ctx.r9.u64 + ctx.r10.u64;
	// subf r4,r9,r10
	ctx.r4.u64 = ctx.r10.u64 - ctx.r9.u64;
	// add r10,r5,r8
	ctx.r10.u64 = ctx.r5.u64 + ctx.r8.u64;
	// add r9,r4,r8
	ctx.r9.u64 = ctx.r4.u64 + ctx.r8.u64;
	// srawi r8,r10,20
	ctx.xer.ca = (ctx.r10.s32 < 0) & ((ctx.r10.u32 & 0xFFFFF) != 0);
	ctx.r8.s64 = ctx.r10.s32 >> 20;
	// srawi r7,r9,20
	ctx.xer.ca = (ctx.r9.s32 < 0) & ((ctx.r9.u32 & 0xFFFFF) != 0);
	ctx.r7.s64 = ctx.r9.s32 >> 20;
	// clrlwi r6,r8,22
	ctx.r6.u64 = ctx.r8.u32 & 0x3FF;
	// clrlwi r5,r7,22
	ctx.r5.u64 = ctx.r7.u32 & 0x3FF;
	// lbzx r4,r6,r3
	ctx.r4.u64 = REX_LOAD_U8(ctx.r6.u32 + ctx.r3.u32);
	// stb r4,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r4.u8);
	// lbzx r3,r5,r3
	ctx.r3.u64 = REX_LOAD_U8(ctx.r5.u32 + ctx.r3.u32);
	// stb r3,1(r11)
	REX_STORE_U8(ctx.r11.u32 + 1, ctx.r3.u8);
	// b 0x9205b4bc
	__restgprlr_25(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92248800) {
	REX_FUNC_PROLOGUE();
	// lwz r11,80(r4)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r4.u32 + 80);
	// lhz r9,0(r5)
	ctx.r9.u64 = REX_LOAD_U16(ctx.r5.u32 + 0);
	// lwz r10,328(r3)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r3.u32 + 328);
	// extsh r8,r9
	ctx.r8.s64 = ctx.r9.s16;
	// lwz r6,0(r6)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r6.u32 + 0);
	// lhz r5,0(r11)
	ctx.r5.u64 = REX_LOAD_U16(ctx.r11.u32 + 0);
	// extsh r4,r5
	ctx.r4.s64 = ctx.r5.s16;
	// mullw r11,r4,r8
	ctx.r11.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r8.s32);
	// addi r3,r11,4
	ctx.r3.s64 = ctx.r11.s64 + 4;
	// srawi r11,r3,3
	ctx.xer.ca = (ctx.r3.s32 < 0) & ((ctx.r3.u32 & 0x7) != 0);
	ctx.r11.s64 = ctx.r3.s32 >> 3;
	// clrlwi r11,r11,22
	ctx.r11.u64 = ctx.r11.u32 & 0x3FF;
	// add r10,r11,r10
	ctx.r10.u64 = ctx.r11.u64 + ctx.r10.u64;
	// lbz r9,128(r10)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r10.u32 + 128);
	// stbx r9,r6,r7
	REX_STORE_U8(ctx.r6.u32 + ctx.r7.u32, ctx.r9.u8);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_92248840) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b45c
	ctx.lr = 0x92248848;
	__savegprlr_21(ctx, base);
	// stwu r1,-176(r1)
	ea = -176 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r31,r4
	ctx.r31.u64 = ctx.r4.u64;
	// lwz r11,52(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 52);
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// lwz r26,4(r30)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r30.u32 + 4);
	// lwz r28,0(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// lwz r24,4(r31)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// lwz r27,32(r30)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// lwz r29,28(r30)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// bge cr6,0x92248884
	if (!ctx.cr6.lt) goto loc_92248884;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x9224888c
	goto loc_9224888C;
loc_92248884:
	// lwz r10,44(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// subf r7,r11,r10
	ctx.r7.u64 = ctx.r10.u64 - ctx.r11.u64;
loc_9224888C:
	// lwz r9,0(r26)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// cmplwi cr6,r9,9
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 9, ctx.xer);
	// bgt cr6,0x92248dcc
	if (ctx.cr6.gt) goto loc_92248DCC;
	// lis r10,-28121
	ctx.r10.s64 = -1842937856;
	// li r21,9
	ctx.r21.s64 = 9;
	// addi r22,r10,-1712
	ctx.r22.s64 = ctx.r10.s64 + -1712;
	// li r23,0
	ctx.r23.s64 = 0;
loc_922488A8:
	// lis r12,-28156
	ctx.r12.s64 = -1845231616;
	// addi r12,r12,3552
	ctx.r12.s64 = ctx.r12.s64 + 3552;
	// rlwinm r0,r9,1,0,30
	ctx.r0.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0xFFFFFFFE;
	// lhzx r0,r12,r0
	ctx.r0.u64 = REX_LOAD_U16(ctx.r12.u32 + ctx.r0.u32);
	// lis r12,-28123
	ctx.r12.s64 = -1843068928;
	// addi r12,r12,-30512
	ctx.r12.s64 = ctx.r12.s64 + -30512;
	// add r12,r12,r0
	ctx.r12.u64 = ctx.r12.u64 + ctx.r0.u64;
	// mtctr r12
	ctx.ctr.u64 = ctx.r12.u64;
	// nop 
	// bctr 
	switch (ctx.r9.u32) {
	case 0:
		goto loc_922488D0;
	case 1:
		goto loc_92248994;
	case 2:
		goto loc_92248A60;
	case 3:
		goto loc_92248ACC;
	case 4:
		goto loc_92248B60;
	case 5:
		goto loc_92248BBC;
	case 6:
		goto loc_92248CEC;
	case 7:
		goto loc_92248E34;
	case 8:
		goto loc_92248E74;
	case 9:
		goto loc_92248E2C;
	default:
		__builtin_trap(); // Switch case out of range
	}
loc_922488D0:
	// cmplwi cr6,r7,258
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 258, ctx.xer);
	// blt cr6,0x9224897c
	if (ctx.cr6.lt) goto loc_9224897C;
	// cmplwi cr6,r24,10
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 10, ctx.xer);
	// blt cr6,0x9224897c
	if (ctx.cr6.lt) goto loc_9224897C;
	// stw r27,32(r30)
	REX_STORE_U32(ctx.r30.u32 + 32, ctx.r27.u32);
	// mr r8,r31
	ctx.r8.u64 = ctx.r31.u64;
	// stw r29,28(r30)
	REX_STORE_U32(ctx.r30.u32 + 28, ctx.r29.u32);
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// lwz r10,0(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// lwz r9,8(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// subf r10,r10,r28
	ctx.r10.u64 = ctx.r28.u64 - ctx.r10.u64;
	// stw r24,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r24.u32);
	// stw r28,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r28.u32);
	// add r10,r10,r9
	ctx.r10.u64 = ctx.r10.u64 + ctx.r9.u64;
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// stw r11,52(r30)
	REX_STORE_U32(ctx.r30.u32 + 52, ctx.r11.u32);
	// lwz r6,24(r26)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r26.u32 + 24);
	// lwz r5,20(r26)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r26.u32 + 20);
	// lbz r4,17(r26)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r26.u32 + 17);
	// lbz r3,16(r26)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r26.u32 + 16);
	// bl 0x92249748
	ctx.lr = 0x92248924;
	sub_92249748(ctx, base);
	// lwz r11,52(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 52);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// lwz r28,0(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// lwz r24,4(r31)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// lwz r27,32(r30)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// lwz r29,28(r30)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// bge cr6,0x92248954
	if (!ctx.cr6.lt) goto loc_92248954;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x9224895c
	goto loc_9224895C;
loc_92248954:
	// lwz r10,44(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// subf r7,r11,r10
	ctx.r7.u64 = ctx.r10.u64 - ctx.r11.u64;
loc_9224895C:
	// cmpwi cr6,r5,0
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// beq cr6,0x9224897c
	if (ctx.cr6.eq) goto loc_9224897C;
	// cmpwi cr6,r5,1
	ctx.cr6.compare<int32_t>(ctx.r5.s32, 1, ctx.xer);
	// li r10,7
	ctx.r10.s64 = 7;
	// beq cr6,0x92248974
	if (ctx.cr6.eq) goto loc_92248974;
	// mr r10,r21
	ctx.r10.u64 = ctx.r21.u64;
loc_92248974:
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x92248dc0
	goto loc_92248DC0;
loc_9224897C:
	// lbz r10,16(r26)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r26.u32 + 16);
	// li r9,1
	ctx.r9.s64 = 1;
	// lwz r8,20(r26)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r26.u32 + 20);
	// stw r10,12(r26)
	REX_STORE_U32(ctx.r26.u32 + 12, ctx.r10.u32);
	// stw r8,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r8.u32);
	// stw r9,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r9.u32);
loc_92248994:
	// lwz r10,12(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 12);
	// b 0x922489c0
	goto loc_922489C0;
loc_9224899C:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92248e0c
	if (ctx.cr6.eq) goto loc_92248E0C;
	// lbz r9,0(r28)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r28.u32 + 0);
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r28,r28,1
	ctx.r28.s64 = ctx.r28.s64 + 1;
	// slw r9,r9,r29
	ctx.r9.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r29.u8 & 0x3F));
	// addi r29,r29,8
	ctx.r29.s64 = ctx.r29.s64 + 8;
	// or r27,r9,r27
	ctx.r27.u64 = ctx.r9.u64 | ctx.r27.u64;
loc_922489C0:
	// cmplw cr6,r29,r10
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, ctx.r10.u32, ctx.xer);
	// blt cr6,0x9224899c
	if (ctx.cr6.lt) goto loc_9224899C;
	// rlwinm r10,r10,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r9,8(r26)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r26.u32 + 8);
	// lwzx r10,r10,r22
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + ctx.r22.u32);
	// and r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 & ctx.r27.u64;
	// rlwinm r10,r10,3,0,28
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0xFFFFFFF8;
	// add r10,r10,r9
	ctx.r10.u64 = ctx.r10.u64 + ctx.r9.u64;
	// lbz r9,1(r10)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r10.u32 + 1);
	// lbz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// subf r29,r9,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r9.u64;
	// cmplwi r8,0
	ctx.cr0.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// srw r27,r27,r9
	ctx.r27.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r9.u8 & 0x3F));
	// bne 0x92248a0c
	if (!ctx.cr0.eq) goto loc_92248A0C;
	// lwz r10,4(r10)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + 4);
	// li r9,6
	ctx.r9.s64 = 6;
	// stw r10,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r10.u32);
	// stw r9,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r9.u32);
	// b 0x92248dc0
	goto loc_92248DC0;
loc_92248A0C:
	// rlwinm. r9,r8,0,27,27
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x10;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x92248a30
	if (ctx.cr0.eq) goto loc_92248A30;
	// clrlwi r9,r8,28
	ctx.r9.u64 = ctx.r8.u32 & 0xF;
	// li r8,2
	ctx.r8.s64 = 2;
	// stw r9,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r9.u32);
	// lwz r10,4(r10)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + 4);
	// stw r8,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r8.u32);
	// stw r10,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r10.u32);
	// b 0x92248dc0
	goto loc_92248DC0;
loc_92248A30:
	// rlwinm. r9,r8,0,25,25
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x40;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// bne 0x92248a50
	if (!ctx.cr0.eq) goto loc_92248A50;
loc_92248A38:
	// stw r8,12(r26)
	REX_STORE_U32(ctx.r26.u32 + 12, ctx.r8.u32);
	// lwz r9,4(r10)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r10.u32 + 4);
	// rlwinm r9,r9,3,0,28
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 3) & 0xFFFFFFF8;
	// add r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 + ctx.r10.u64;
	// stw r10,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r10.u32);
	// b 0x92248dc0
	goto loc_92248DC0;
loc_92248A50:
	// rlwinm. r10,r8,0,26,26
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x20;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// beq 0x92248e1c
	if (ctx.cr0.eq) goto loc_92248E1C;
	// li r10,7
	ctx.r10.s64 = 7;
	// b 0x92248974
	goto loc_92248974;
loc_92248A60:
	// lwz r10,8(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 8);
	// b 0x92248a8c
	goto loc_92248A8C;
loc_92248A68:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92248e0c
	if (ctx.cr6.eq) goto loc_92248E0C;
	// lbz r9,0(r28)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r28.u32 + 0);
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r28,r28,1
	ctx.r28.s64 = ctx.r28.s64 + 1;
	// slw r9,r9,r29
	ctx.r9.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r29.u8 & 0x3F));
	// addi r29,r29,8
	ctx.r29.s64 = ctx.r29.s64 + 8;
	// or r27,r9,r27
	ctx.r27.u64 = ctx.r9.u64 | ctx.r27.u64;
loc_92248A8C:
	// cmplw cr6,r29,r10
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, ctx.r10.u32, ctx.xer);
	// blt cr6,0x92248a68
	if (ctx.cr6.lt) goto loc_92248A68;
	// rlwinm r6,r10,2,0,29
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// lbz r9,17(r26)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r26.u32 + 17);
	// subf r29,r10,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r10.u64;
	// lwz r8,24(r26)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r26.u32 + 24);
	// li r4,3
	ctx.r4.s64 = 3;
	// lwzx r6,r6,r22
	ctx.r6.u64 = REX_LOAD_U32(ctx.r6.u32 + ctx.r22.u32);
	// stw r9,12(r26)
	REX_STORE_U32(ctx.r26.u32 + 12, ctx.r9.u32);
	// and r9,r6,r27
	ctx.r9.u64 = ctx.r6.u64 & ctx.r27.u64;
	// stw r8,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r8.u32);
	// srw r27,r27,r10
	ctx.r27.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r10.u8 & 0x3F));
	// lwz r10,4(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// stw r4,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r4.u32);
	// add r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 + ctx.r10.u64;
	// stw r10,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r10.u32);
loc_92248ACC:
	// lwz r10,12(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 12);
	// b 0x92248af8
	goto loc_92248AF8;
loc_92248AD4:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92248e0c
	if (ctx.cr6.eq) goto loc_92248E0C;
	// lbz r9,0(r28)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r28.u32 + 0);
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r28,r28,1
	ctx.r28.s64 = ctx.r28.s64 + 1;
	// slw r9,r9,r29
	ctx.r9.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r29.u8 & 0x3F));
	// addi r29,r29,8
	ctx.r29.s64 = ctx.r29.s64 + 8;
	// or r27,r9,r27
	ctx.r27.u64 = ctx.r9.u64 | ctx.r27.u64;
loc_92248AF8:
	// cmplw cr6,r29,r10
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, ctx.r10.u32, ctx.xer);
	// blt cr6,0x92248ad4
	if (ctx.cr6.lt) goto loc_92248AD4;
	// rlwinm r10,r10,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r9,8(r26)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r26.u32 + 8);
	// lwzx r10,r10,r22
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + ctx.r22.u32);
	// and r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 & ctx.r27.u64;
	// rlwinm r10,r10,3,0,28
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0xFFFFFFF8;
	// add r10,r10,r9
	ctx.r10.u64 = ctx.r10.u64 + ctx.r9.u64;
	// lbz r9,1(r10)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r10.u32 + 1);
	// lbz r8,0(r10)
	ctx.r8.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// subf r29,r9,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r9.u64;
	// srw r27,r27,r9
	ctx.r27.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r9.u8 & 0x3F));
	// rlwinm. r6,r8,0,27,27
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x10;
	ctx.cr0.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// beq 0x92248b4c
	if (ctx.cr0.eq) goto loc_92248B4C;
	// clrlwi r9,r8,28
	ctx.r9.u64 = ctx.r8.u32 & 0xF;
	// li r8,4
	ctx.r8.s64 = 4;
	// stw r9,8(r26)
	REX_STORE_U32(ctx.r26.u32 + 8, ctx.r9.u32);
	// lwz r10,4(r10)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + 4);
	// stw r8,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r8.u32);
	// stw r10,12(r26)
	REX_STORE_U32(ctx.r26.u32 + 12, ctx.r10.u32);
	// b 0x92248dc0
	goto loc_92248DC0;
loc_92248B4C:
	// rlwinm. r9,r8,0,25,25
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x40;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x92248a38
	if (ctx.cr0.eq) goto loc_92248A38;
	// lis r10,-28157
	ctx.r10.s64 = -1845297152;
	// addi r10,r10,19976
	ctx.r10.s64 = ctx.r10.s64 + 19976;
	// b 0x92248e24
	goto loc_92248E24;
loc_92248B60:
	// lwz r10,8(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 8);
	// b 0x92248b8c
	goto loc_92248B8C;
loc_92248B68:
	// cmplwi cr6,r24,0
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, 0, ctx.xer);
	// beq cr6,0x92248e0c
	if (ctx.cr6.eq) goto loc_92248E0C;
	// lbz r9,0(r28)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r28.u32 + 0);
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
	// addi r28,r28,1
	ctx.r28.s64 = ctx.r28.s64 + 1;
	// slw r9,r9,r29
	ctx.r9.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r29.u8 & 0x3F));
	// addi r29,r29,8
	ctx.r29.s64 = ctx.r29.s64 + 8;
	// or r27,r9,r27
	ctx.r27.u64 = ctx.r9.u64 | ctx.r27.u64;
loc_92248B8C:
	// cmplw cr6,r29,r10
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, ctx.r10.u32, ctx.xer);
	// blt cr6,0x92248b68
	if (ctx.cr6.lt) goto loc_92248B68;
	// rlwinm r9,r10,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// subf r29,r10,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r10.u64;
	// li r8,5
	ctx.r8.s64 = 5;
	// lwzx r9,r9,r22
	ctx.r9.u64 = REX_LOAD_U32(ctx.r9.u32 + ctx.r22.u32);
	// and r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 & ctx.r27.u64;
	// stw r8,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r8.u32);
	// srw r27,r27,r10
	ctx.r27.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r27.u32 >> (ctx.r10.u8 & 0x3F));
	// lwz r10,12(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 12);
	// add r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 + ctx.r10.u64;
	// stw r10,12(r26)
	REX_STORE_U32(ctx.r26.u32 + 12, ctx.r10.u32);
loc_92248BBC:
	// lwz r9,40(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// lwz r10,12(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 12);
	// subf r8,r9,r11
	ctx.r8.u64 = ctx.r11.u64 - ctx.r9.u64;
	// cmplw cr6,r8,r10
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248be4
	if (!ctx.cr6.lt) goto loc_92248BE4;
	// lwz r8,44(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// subf r9,r9,r8
	ctx.r9.u64 = ctx.r8.u64 - ctx.r9.u64;
	// subf r10,r10,r9
	ctx.r10.u64 = ctx.r9.u64 - ctx.r10.u64;
	// add r25,r10,r11
	ctx.r25.u64 = ctx.r10.u64 + ctx.r11.u64;
	// b 0x92248cdc
	goto loc_92248CDC;
loc_92248BE4:
	// subf r25,r10,r11
	ctx.r25.u64 = ctx.r11.u64 - ctx.r10.u64;
	// b 0x92248cdc
	goto loc_92248CDC;
loc_92248BEC:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// bne cr6,0x92248ca8
	if (!ctx.cr6.eq) goto loc_92248CA8;
	// lwz r8,44(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplw cr6,r11,r8
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r8.u32, ctx.xer);
	// bne cr6,0x92248c34
	if (!ctx.cr6.eq) goto loc_92248C34;
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// lwz r9,40(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// cmplw cr6,r10,r9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
	// beq cr6,0x92248c34
	if (ctx.cr6.eq) goto loc_92248C34;
	// mr r11,r9
	ctx.r11.u64 = ctx.r9.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248c28
	if (!ctx.cr6.lt) goto loc_92248C28;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x92248c2c
	goto loc_92248C2C;
loc_92248C28:
	// subf r7,r11,r8
	ctx.r7.u64 = ctx.r8.u64 - ctx.r11.u64;
loc_92248C2C:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// bne cr6,0x92248ca8
	if (!ctx.cr6.eq) goto loc_92248CA8;
loc_92248C34:
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// stw r11,52(r30)
	REX_STORE_U32(ctx.r30.u32 + 52, ctx.r11.u32);
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x922495e8
	ctx.lr = 0x92248C44;
	sub_922495E8(ctx, base);
	// lwz r11,52(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 52);
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248c64
	if (!ctx.cr6.lt) goto loc_92248C64;
	// subf r9,r11,r10
	ctx.r9.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r9,-1
	ctx.r7.s64 = ctx.r9.s64 + -1;
	// b 0x92248c6c
	goto loc_92248C6C;
loc_92248C64:
	// lwz r9,44(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// subf r7,r11,r9
	ctx.r7.u64 = ctx.r9.u64 - ctx.r11.u64;
loc_92248C6C:
	// lwz r8,44(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplw cr6,r11,r8
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r8.u32, ctx.xer);
	// bne cr6,0x92248ca0
	if (!ctx.cr6.eq) goto loc_92248CA0;
	// lwz r9,40(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// cmplw cr6,r10,r9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
	// beq cr6,0x92248ca0
	if (ctx.cr6.eq) goto loc_92248CA0;
	// mr r11,r9
	ctx.r11.u64 = ctx.r9.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248c9c
	if (!ctx.cr6.lt) goto loc_92248C9C;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x92248ca0
	goto loc_92248CA0;
loc_92248C9C:
	// subf r7,r11,r8
	ctx.r7.u64 = ctx.r8.u64 - ctx.r11.u64;
loc_92248CA0:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// beq cr6,0x92248dd0
	if (ctx.cr6.eq) goto loc_92248DD0;
loc_92248CA8:
	// lbz r10,0(r25)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r25.u32 + 0);
	// addi r25,r25,1
	ctx.r25.s64 = ctx.r25.s64 + 1;
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r7,r7,-1
	ctx.r7.s64 = ctx.r7.s64 + -1;
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// lwz r10,44(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplw cr6,r25,r10
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, ctx.r10.u32, ctx.xer);
	// bne cr6,0x92248cd0
	if (!ctx.cr6.eq) goto loc_92248CD0;
	// lwz r25,40(r30)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
loc_92248CD0:
	// lwz r10,4(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// stw r10,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r10.u32);
loc_92248CDC:
	// lwz r10,4(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// bne cr6,0x92248bec
	if (!ctx.cr6.eq) goto loc_92248BEC;
	// b 0x92248dbc
	goto loc_92248DBC;
loc_92248CEC:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// bne cr6,0x92248da8
	if (!ctx.cr6.eq) goto loc_92248DA8;
	// lwz r8,44(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplw cr6,r11,r8
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r8.u32, ctx.xer);
	// bne cr6,0x92248d34
	if (!ctx.cr6.eq) goto loc_92248D34;
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// lwz r9,40(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// cmplw cr6,r10,r9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
	// beq cr6,0x92248d34
	if (ctx.cr6.eq) goto loc_92248D34;
	// mr r11,r9
	ctx.r11.u64 = ctx.r9.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248d28
	if (!ctx.cr6.lt) goto loc_92248D28;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x92248d2c
	goto loc_92248D2C;
loc_92248D28:
	// subf r7,r11,r8
	ctx.r7.u64 = ctx.r8.u64 - ctx.r11.u64;
loc_92248D2C:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// bne cr6,0x92248da8
	if (!ctx.cr6.eq) goto loc_92248DA8;
loc_92248D34:
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// stw r11,52(r30)
	REX_STORE_U32(ctx.r30.u32 + 52, ctx.r11.u32);
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x922495e8
	ctx.lr = 0x92248D44;
	sub_922495E8(ctx, base);
	// lwz r11,52(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 52);
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248d64
	if (!ctx.cr6.lt) goto loc_92248D64;
	// subf r9,r11,r10
	ctx.r9.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r9,-1
	ctx.r7.s64 = ctx.r9.s64 + -1;
	// b 0x92248d6c
	goto loc_92248D6C;
loc_92248D64:
	// lwz r9,44(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// subf r7,r11,r9
	ctx.r7.u64 = ctx.r9.u64 - ctx.r11.u64;
loc_92248D6C:
	// lwz r8,44(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplw cr6,r11,r8
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r8.u32, ctx.xer);
	// bne cr6,0x92248da0
	if (!ctx.cr6.eq) goto loc_92248DA0;
	// lwz r9,40(r30)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r30.u32 + 40);
	// cmplw cr6,r10,r9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
	// beq cr6,0x92248da0
	if (ctx.cr6.eq) goto loc_92248DA0;
	// mr r11,r9
	ctx.r11.u64 = ctx.r9.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bge cr6,0x92248d9c
	if (!ctx.cr6.lt) goto loc_92248D9C;
	// subf r10,r11,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r11.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// b 0x92248da0
	goto loc_92248DA0;
loc_92248D9C:
	// subf r7,r11,r8
	ctx.r7.u64 = ctx.r8.u64 - ctx.r11.u64;
loc_92248DA0:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// beq cr6,0x92248dd0
	if (ctx.cr6.eq) goto loc_92248DD0;
loc_92248DA8:
	// lwz r10,8(r26)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r26.u32 + 8);
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// addi r7,r7,-1
	ctx.r7.s64 = ctx.r7.s64 + -1;
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
loc_92248DBC:
	// stw r23,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r23.u32);
loc_92248DC0:
	// lwz r9,0(r26)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// cmplwi cr6,r9,9
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 9, ctx.xer);
	// ble cr6,0x922488a8
	if (!ctx.cr6.gt) goto loc_922488A8;
loc_92248DCC:
	// li r5,-2
	ctx.r5.s64 = -2;
loc_92248DD0:
	// stw r27,32(r30)
	REX_STORE_U32(ctx.r30.u32 + 32, ctx.r27.u32);
	// stw r29,28(r30)
	REX_STORE_U32(ctx.r30.u32 + 28, ctx.r29.u32);
	// stw r24,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r24.u32);
loc_92248DDC:
	// lwz r10,0(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// lwz r9,8(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// subf r10,r10,r28
	ctx.r10.u64 = ctx.r28.u64 - ctx.r10.u64;
	// stw r28,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r28.u32);
	// add r10,r10,r9
	ctx.r10.u64 = ctx.r10.u64 + ctx.r9.u64;
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// stw r11,52(r30)
	REX_STORE_U32(ctx.r30.u32 + 52, ctx.r11.u32);
	// bl 0x922495e8
	ctx.lr = 0x92248E04;
	sub_922495E8(ctx, base);
	// addi r1,r1,176
	ctx.r1.s64 = ctx.r1.s64 + 176;
	// b 0x9205b4ac
	__restgprlr_21(ctx, base);
	return;
loc_92248E0C:
	// stw r27,32(r30)
	REX_STORE_U32(ctx.r30.u32 + 32, ctx.r27.u32);
	// stw r29,28(r30)
	REX_STORE_U32(ctx.r30.u32 + 28, ctx.r29.u32);
	// stw r23,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r23.u32);
	// b 0x92248ddc
	goto loc_92248DDC;
loc_92248E1C:
	// lis r10,-28157
	ctx.r10.s64 = -1845297152;
	// addi r10,r10,19948
	ctx.r10.s64 = ctx.r10.s64 + 19948;
loc_92248E24:
	// stw r21,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r21.u32);
	// stw r10,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r10.u32);
loc_92248E2C:
	// li r5,-3
	ctx.r5.s64 = -3;
	// b 0x92248dd0
	goto loc_92248DD0;
loc_92248E34:
	// cmplwi cr6,r29,7
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 7, ctx.xer);
	// ble cr6,0x92248e48
	if (!ctx.cr6.gt) goto loc_92248E48;
	// addi r29,r29,-8
	ctx.r29.s64 = ctx.r29.s64 + -8;
	// addi r24,r24,1
	ctx.r24.s64 = ctx.r24.s64 + 1;
	// addi r28,r28,-1
	ctx.r28.s64 = ctx.r28.s64 + -1;
loc_92248E48:
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// stw r11,52(r30)
	REX_STORE_U32(ctx.r30.u32 + 52, ctx.r11.u32);
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x922495e8
	ctx.lr = 0x92248E58;
	sub_922495E8(ctx, base);
	// lwz r11,52(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 52);
	// lwz r10,48(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 48);
	// mr r5,r3
	ctx.r5.u64 = ctx.r3.u64;
	// cmplw cr6,r10,r11
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r11.u32, ctx.xer);
	// bne cr6,0x92248dd0
	if (!ctx.cr6.eq) goto loc_92248DD0;
	// li r10,8
	ctx.r10.s64 = 8;
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
loc_92248E74:
	// li r5,1
	ctx.r5.s64 = 1;
	// b 0x92248dd0
	goto loc_92248DD0;
}

DEFINE_REX_FUNC(sub_92248E80) {
	REX_FUNC_PROLOGUE();
	// mr r11,r4
	ctx.r11.u64 = ctx.r4.u64;
	// mr r10,r3
	ctx.r10.u64 = ctx.r3.u64;
	// mr r4,r10
	ctx.r4.u64 = ctx.r10.u64;
	// lwz r3,40(r11)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r11.u32 + 40);
	// lwz r11,36(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctr 
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	return;
}

DEFINE_REX_FUNC(sub_92248EA0) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x92248EA8;
	__savegprlr_14(ctx, base);
	// li r27,0
	ctx.r27.s64 = 0;
	// stw r6,44(r1)
	REX_STORE_U32(ctx.r1.u32 + 44, ctx.r6.u32);
	// stw r7,52(r1)
	REX_STORE_U32(ctx.r1.u32 + 52, ctx.r7.u32);
	// mr r6,r10
	ctx.r6.u64 = ctx.r10.u64;
	// stw r8,60(r1)
	REX_STORE_U32(ctx.r1.u32 + 60, ctx.r8.u32);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r11,r4
	ctx.r11.u64 = ctx.r4.u64;
	// stw r27,-352(r1)
	REX_STORE_U32(ctx.r1.u32 + -352, ctx.r27.u32);
	// stw r27,-348(r1)
	REX_STORE_U32(ctx.r1.u32 + -348, ctx.r27.u32);
	// stw r27,-344(r1)
	REX_STORE_U32(ctx.r1.u32 + -344, ctx.r27.u32);
	// stw r27,-340(r1)
	REX_STORE_U32(ctx.r1.u32 + -340, ctx.r27.u32);
	// stw r27,-336(r1)
	REX_STORE_U32(ctx.r1.u32 + -336, ctx.r27.u32);
	// stw r27,-332(r1)
	REX_STORE_U32(ctx.r1.u32 + -332, ctx.r27.u32);
	// stw r27,-328(r1)
	REX_STORE_U32(ctx.r1.u32 + -328, ctx.r27.u32);
	// stw r27,-324(r1)
	REX_STORE_U32(ctx.r1.u32 + -324, ctx.r27.u32);
	// stw r27,-320(r1)
	REX_STORE_U32(ctx.r1.u32 + -320, ctx.r27.u32);
	// stw r27,-316(r1)
	REX_STORE_U32(ctx.r1.u32 + -316, ctx.r27.u32);
	// stw r27,-312(r1)
	REX_STORE_U32(ctx.r1.u32 + -312, ctx.r27.u32);
	// stw r27,-308(r1)
	REX_STORE_U32(ctx.r1.u32 + -308, ctx.r27.u32);
	// stw r27,-304(r1)
	REX_STORE_U32(ctx.r1.u32 + -304, ctx.r27.u32);
	// stw r27,-300(r1)
	REX_STORE_U32(ctx.r1.u32 + -300, ctx.r27.u32);
	// stw r27,-296(r1)
	REX_STORE_U32(ctx.r1.u32 + -296, ctx.r27.u32);
	// stw r27,-292(r1)
	REX_STORE_U32(ctx.r1.u32 + -292, ctx.r27.u32);
loc_92248F04:
	// lwz r10,0(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// addi r29,r1,-352
	ctx.r29.s64 = ctx.r1.s64 + -352;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// rlwinm r30,r10,2,0,29
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r31,r31,4
	ctx.r31.s64 = ctx.r31.s64 + 4;
	// lwzx r28,r30,r29
	ctx.r28.u64 = REX_LOAD_U32(ctx.r30.u32 + ctx.r29.u32);
	// addi r10,r28,1
	ctx.r10.s64 = ctx.r28.s64 + 1;
	// stwx r10,r30,r29
	REX_STORE_U32(ctx.r30.u32 + ctx.r29.u32, ctx.r10.u32);
	// bne 0x92248f04
	if (!ctx.cr0.eq) goto loc_92248F04;
	// lwz r11,-352(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -352);
	// cmplw cr6,r11,r4
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r4.u32, ctx.xer);
	// bne cr6,0x92248f44
	if (!ctx.cr6.eq) goto loc_92248F44;
	// stw r27,0(r8)
	REX_STORE_U32(ctx.r8.u32 + 0, ctx.r27.u32);
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r27,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r27.u32);
	// b 0x9224930c
	goto loc_9224930C;
loc_92248F44:
	// li r10,1
	ctx.r10.s64 = 1;
	// lwz r22,0(r9)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r9.u32 + 0);
	// addi r31,r1,-348
	ctx.r31.s64 = ctx.r1.s64 + -348;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
loc_92248F54:
	// lwz r8,0(r31)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// cmplwi cr6,r8,0
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// bne cr6,0x92248f70
	if (!ctx.cr6.eq) goto loc_92248F70;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r31,r31,4
	ctx.r31.s64 = ctx.r31.s64 + 4;
	// cmplwi cr6,r11,15
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 15, ctx.xer);
	// ble cr6,0x92248f54
	if (!ctx.cr6.gt) goto loc_92248F54;
loc_92248F70:
	// mr r17,r11
	ctx.r17.u64 = ctx.r11.u64;
	// cmplw cr6,r22,r11
	ctx.cr6.compare<uint32_t>(ctx.r22.u32, ctx.r11.u32, ctx.xer);
	// bge cr6,0x92248f80
	if (!ctx.cr6.lt) goto loc_92248F80;
	// mr r22,r11
	ctx.r22.u64 = ctx.r11.u64;
loc_92248F80:
	// li r31,15
	ctx.r31.s64 = 15;
	// addi r30,r1,-292
	ctx.r30.s64 = ctx.r1.s64 + -292;
loc_92248F88:
	// lwz r8,0(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// cmplwi cr6,r8,0
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// bne cr6,0x92248fa0
	if (!ctx.cr6.eq) goto loc_92248FA0;
	// addic. r31,r31,-1
	ctx.xer.ca = ctx.r31.u32 > 0;
	ctx.r31.s64 = ctx.r31.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// addi r30,r30,-4
	ctx.r30.s64 = ctx.r30.s64 + -4;
	// bne 0x92248f88
	if (!ctx.cr0.eq) goto loc_92248F88;
loc_92248FA0:
	// mr r7,r31
	ctx.r7.u64 = ctx.r31.u64;
	// cmplw cr6,r22,r31
	ctx.cr6.compare<uint32_t>(ctx.r22.u32, ctx.r31.u32, ctx.xer);
	// ble cr6,0x92248fb0
	if (!ctx.cr6.gt) goto loc_92248FB0;
	// mr r22,r31
	ctx.r22.u64 = ctx.r31.u64;
loc_92248FB0:
	// cmplw cr6,r11,r31
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r31.u32, ctx.xer);
	// stw r22,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r22.u32);
	// slw r29,r10,r11
	ctx.r29.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// bge cr6,0x92248fec
	if (!ctx.cr6.lt) goto loc_92248FEC;
	// rlwinm r9,r11,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r30,r1,-352
	ctx.r30.s64 = ctx.r1.s64 + -352;
	// add r9,r9,r30
	ctx.r9.u64 = ctx.r9.u64 + ctx.r30.u64;
loc_92248FCC:
	// lwz r8,0(r9)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r9.u32 + 0);
	// subf. r30,r8,r29
	ctx.r30.u64 = ctx.r29.u64 - ctx.r8.u64;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// blt 0x92249134
	if (ctx.cr0.lt) goto loc_92249134;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r9,r9,4
	ctx.r9.s64 = ctx.r9.s64 + 4;
	// rlwinm r29,r30,1,0,30
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 1) & 0xFFFFFFFE;
	// cmplw cr6,r11,r31
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r31.u32, ctx.xer);
	// blt cr6,0x92248fcc
	if (ctx.cr6.lt) goto loc_92248FCC;
loc_92248FEC:
	// rlwinm r28,r31,2,0,29
	ctx.r28.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r30,r1,-352
	ctx.r30.s64 = ctx.r1.s64 + -352;
	// lwzx r9,r28,r30
	ctx.r9.u64 = REX_LOAD_U32(ctx.r28.u32 + ctx.r30.u32);
	// subf. r8,r9,r29
	ctx.r8.u64 = ctx.r29.u64 - ctx.r9.u64;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// blt 0x92249134
	if (ctx.cr0.lt) goto loc_92249134;
	// addic. r11,r31,-1
	ctx.xer.ca = ctx.r31.u32 > 0;
	ctx.r11.s64 = ctx.r31.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r27,-284(r1)
	REX_STORE_U32(ctx.r1.u32 + -284, ctx.r27.u32);
	// add r31,r9,r8
	ctx.r31.u64 = ctx.r9.u64 + ctx.r8.u64;
	// mr r9,r27
	ctx.r9.u64 = ctx.r27.u64;
	// stwx r31,r28,r30
	REX_STORE_U32(ctx.r28.u32 + ctx.r30.u32, ctx.r31.u32);
	// beq 0x9224903c
	if (ctx.cr0.eq) goto loc_9224903C;
	// mr r31,r27
	ctx.r31.u64 = ctx.r27.u64;
loc_9224901C:
	// addi r30,r1,-348
	ctx.r30.s64 = ctx.r1.s64 + -348;
	// addi r29,r1,-280
	ctx.r29.s64 = ctx.r1.s64 + -280;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// lwzx r30,r31,r30
	ctx.r30.u64 = REX_LOAD_U32(ctx.r31.u32 + ctx.r30.u32);
	// add r9,r30,r9
	ctx.r9.u64 = ctx.r30.u64 + ctx.r9.u64;
	// stwx r9,r31,r29
	REX_STORE_U32(ctx.r31.u32 + ctx.r29.u32, ctx.r9.u32);
	// addi r31,r31,4
	ctx.r31.s64 = ctx.r31.s64 + 4;
	// bne 0x9224901c
	if (!ctx.cr0.eq) goto loc_9224901C;
loc_9224903C:
	// lwz r15,92(r1)
	ctx.r15.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r31,r27
	ctx.r31.u64 = ctx.r27.u64;
loc_92249048:
	// lwz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// addi r30,r30,4
	ctx.r30.s64 = ctx.r30.s64 + 4;
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq 0x92249074
	if (ctx.cr0.eq) goto loc_92249074;
	// rlwinm r9,r11,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r3,r1,-288
	ctx.r3.s64 = ctx.r1.s64 + -288;
	// lwzx r11,r9,r3
	ctx.r11.u64 = REX_LOAD_U32(ctx.r9.u32 + ctx.r3.u32);
	// rlwinm r29,r11,2,0,29
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stwx r31,r29,r15
	REX_STORE_U32(ctx.r29.u32 + ctx.r15.u32, ctx.r31.u32);
	// stwx r11,r9,r3
	REX_STORE_U32(ctx.r9.u32 + ctx.r3.u32, ctx.r11.u32);
loc_92249074:
	// addi r31,r31,1
	ctx.r31.s64 = ctx.r31.s64 + 1;
	// cmplw cr6,r31,r4
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r4.u32, ctx.xer);
	// blt cr6,0x92249048
	if (ctx.cr6.lt) goto loc_92249048;
	// addi r11,r1,-288
	ctx.r11.s64 = ctx.r1.s64 + -288;
	// stw r27,-224(r1)
	REX_STORE_U32(ctx.r1.u32 + -224, ctx.r27.u32);
	// mr r26,r27
	ctx.r26.u64 = ctx.r27.u64;
	// mr r20,r15
	ctx.r20.u64 = ctx.r15.u64;
	// li r24,-1
	ctx.r24.s64 = -1;
	// neg r30,r22
	ctx.r30.s64 = static_cast<int64_t>(-ctx.r22.u64);
	// lwzx r14,r28,r11
	ctx.r14.u64 = REX_LOAD_U32(ctx.r28.u32 + ctx.r11.u32);
	// mr r31,r27
	ctx.r31.u64 = ctx.r27.u64;
	// stw r27,-288(r1)
	REX_STORE_U32(ctx.r1.u32 + -288, ctx.r27.u32);
	// mr r23,r27
	ctx.r23.u64 = ctx.r27.u64;
	// cmpw cr6,r17,r7
	ctx.cr6.compare<int32_t>(ctx.r17.s32, ctx.r7.s32, ctx.xer);
	// bgt cr6,0x922492f4
	if (ctx.cr6.gt) goto loc_922492F4;
	// rlwinm r11,r17,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r17.u32 | (ctx.r17.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r18,84(r1)
	ctx.r18.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r9,r1,-352
	ctx.r9.s64 = ctx.r1.s64 + -352;
	// addi r16,r17,-1
	ctx.r16.s64 = ctx.r17.s64 + -1;
	// add r19,r11,r9
	ctx.r19.u64 = ctx.r11.u64 + ctx.r9.u64;
loc_922490C4:
	// lwz r21,0(r19)
	ctx.r21.u64 = REX_LOAD_U32(ctx.r19.u32 + 0);
	// cmplwi r21,0
	ctx.cr0.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// beq 0x922492e0
	if (ctx.cr0.eq) goto loc_922492E0;
loc_922490D0:
	// add r11,r30,r22
	ctx.r11.u64 = ctx.r30.u64 + ctx.r22.u64;
	// addi r21,r21,-1
	ctx.r21.s64 = ctx.r21.s64 + -1;
	// cmpw cr6,r17,r11
	ctx.cr6.compare<int32_t>(ctx.r17.s32, ctx.r11.s32, ctx.xer);
	// ble cr6,0x922491e0
	if (!ctx.cr6.gt) goto loc_922491E0;
	// addi r25,r21,1
	ctx.r25.s64 = ctx.r21.s64 + 1;
	// mr r28,r11
	ctx.r28.u64 = ctx.r11.u64;
	// subf r29,r22,r30
	ctx.r29.u64 = ctx.r30.u64 - ctx.r22.u64;
loc_922490EC:
	// add r30,r30,r22
	ctx.r30.u64 = ctx.r30.u64 + ctx.r22.u64;
	// addi r24,r24,1
	ctx.r24.s64 = ctx.r24.s64 + 1;
	// subf r9,r30,r7
	ctx.r9.u64 = ctx.r7.u64 - ctx.r30.u64;
	// add r29,r29,r22
	ctx.r29.u64 = ctx.r29.u64 + ctx.r22.u64;
	// add r28,r28,r22
	ctx.r28.u64 = ctx.r28.u64 + ctx.r22.u64;
	// cmplw cr6,r9,r22
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r22.u32, ctx.xer);
	// ble cr6,0x9224910c
	if (!ctx.cr6.gt) goto loc_9224910C;
	// mr r9,r22
	ctx.r9.u64 = ctx.r22.u64;
loc_9224910C:
	// subf r11,r30,r17
	ctx.r11.u64 = ctx.r17.u64 - ctx.r30.u64;
	// slw r4,r10,r11
	ctx.r4.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// cmplw cr6,r4,r25
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, ctx.r25.u32, ctx.xer);
	// ble cr6,0x92249160
	if (!ctx.cr6.gt) goto loc_92249160;
	// subf r4,r21,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r21.u64;
	// mr r3,r19
	ctx.r3.u64 = ctx.r19.u64;
	// addi r4,r4,-1
	ctx.r4.s64 = ctx.r4.s64 + -1;
	// cmplw cr6,r11,r9
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x92249160
	if (!ctx.cr6.lt) goto loc_92249160;
	// b 0x92249154
	goto loc_92249154;
loc_92249134:
	// li r3,-3
	ctx.r3.s64 = -3;
	// b 0x9224930c
	goto loc_9224930C;
loc_9224913C:
	// addi r3,r3,4
	ctx.r3.s64 = ctx.r3.s64 + 4;
	// rlwinm r4,r4,1,0,30
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 1) & 0xFFFFFFFE;
	// lwz r31,0(r3)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r3.u32 + 0);
	// cmplw cr6,r4,r31
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, ctx.r31.u32, ctx.xer);
	// ble cr6,0x92249160
	if (!ctx.cr6.gt) goto loc_92249160;
	// subf r4,r31,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r31.u64;
loc_92249154:
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// cmplw cr6,r11,r9
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r9.u32, ctx.xer);
	// blt cr6,0x9224913c
	if (ctx.cr6.lt) goto loc_9224913C;
loc_92249160:
	// lwz r4,0(r18)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r18.u32 + 0);
	// slw r23,r10,r11
	ctx.r23.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// add r3,r4,r23
	ctx.r3.u64 = ctx.r4.u64 + ctx.r23.u64;
	// cmplwi cr6,r3,1440
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 1440, ctx.xer);
	// bgt cr6,0x92249310
	if (ctx.cr6.gt) goto loc_92249310;
	// rlwinm r31,r4,3,0,28
	ctx.r31.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 3) & 0xFFFFFFF8;
	// stw r3,0(r18)
	REX_STORE_U32(ctx.r18.u32 + 0, ctx.r3.u32);
	// rlwinm r9,r24,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r24.u32 | (ctx.r24.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r4,r1,-224
	ctx.r4.s64 = ctx.r1.s64 + -224;
	// add r31,r31,r6
	ctx.r31.u64 = ctx.r31.u64 + ctx.r6.u64;
	// add r4,r9,r4
	ctx.r4.u64 = ctx.r9.u64 + ctx.r4.u64;
	// cmpwi cr6,r24,0
	ctx.cr6.compare<int32_t>(ctx.r24.s32, 0, ctx.xer);
	// stw r31,0(r4)
	REX_STORE_U32(ctx.r4.u32 + 0, ctx.r31.u32);
	// beq cr6,0x922491d0
	if (ctx.cr6.eq) goto loc_922491D0;
	// stb r11,-368(r1)
	REX_STORE_U8(ctx.r1.u32 + -368, ctx.r11.u8);
	// addi r11,r1,-288
	ctx.r11.s64 = ctx.r1.s64 + -288;
	// lwz r4,-4(r4)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r4.u32 + -4);
	// stb r22,-367(r1)
	REX_STORE_U8(ctx.r1.u32 + -367, ctx.r22.u8);
	// stwx r26,r9,r11
	REX_STORE_U32(ctx.r9.u32 + ctx.r11.u32, ctx.r26.u32);
	// subf r9,r4,r31
	ctx.r9.u64 = ctx.r31.u64 - ctx.r4.u64;
	// srawi r9,r9,3
	ctx.xer.ca = (ctx.r9.s32 < 0) & ((ctx.r9.u32 & 0x7) != 0);
	ctx.r9.s64 = ctx.r9.s32 >> 3;
	// srw r11,r26,r29
	ctx.r11.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r26.u32 >> (ctx.r29.u8 & 0x3F));
	// subf r9,r11,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// stw r9,-364(r1)
	REX_STORE_U32(ctx.r1.u32 + -364, ctx.r9.u32);
	// ld r9,-368(r1)
	ctx.r9.u64 = REX_LOAD_U64(ctx.r1.u32 + -368);
	// stdx r9,r11,r4
	REX_STORE_U64(ctx.r11.u32 + ctx.r4.u32, ctx.r9.u64);
	// b 0x922491d8
	goto loc_922491D8;
loc_922491D0:
	// lwz r11,60(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 60);
	// stw r31,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r31.u32);
loc_922491D8:
	// cmpw cr6,r17,r28
	ctx.cr6.compare<int32_t>(ctx.r17.s32, ctx.r28.s32, ctx.xer);
	// bgt cr6,0x922490ec
	if (ctx.cr6.gt) goto loc_922490EC;
loc_922491E0:
	// rlwinm r11,r14,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r14.u32 | (ctx.r14.u64 << 32), 2) & 0xFFFFFFFC;
	// subf r9,r30,r17
	ctx.r9.u64 = ctx.r17.u64 - ctx.r30.u64;
	// add r11,r11,r15
	ctx.r11.u64 = ctx.r11.u64 + ctx.r15.u64;
	// cmplw cr6,r20,r11
	ctx.cr6.compare<uint32_t>(ctx.r20.u32, ctx.r11.u32, ctx.xer);
	// stb r9,-367(r1)
	REX_STORE_U8(ctx.r1.u32 + -367, ctx.r9.u8);
	// blt cr6,0x92249200
	if (ctx.cr6.lt) goto loc_92249200;
	// li r11,192
	ctx.r11.s64 = 192;
	// b 0x92249250
	goto loc_92249250;
loc_92249200:
	// lwz r11,0(r20)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// addi r20,r20,4
	ctx.r20.s64 = ctx.r20.s64 + 4;
	// cmplw cr6,r11,r5
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r5.u32, ctx.xer);
	// bge cr6,0x92249230
	if (!ctx.cr6.lt) goto loc_92249230;
	// li r9,256
	ctx.r9.s64 = 256;
	// stw r11,-364(r1)
	REX_STORE_U32(ctx.r1.u32 + -364, ctx.r11.u32);
	// subfc r11,r9,r11
	ctx.xer.ca = ctx.r11.u32 >= ctx.r9.u32;
	ctx.r11.u64 = ctx.r11.u64 - ctx.r9.u64;
	// subfe r11,r11,r11
	temp.u8 = (~ctx.r11.u32 + ctx.r11.u32 < ~ctx.r11.u32) | (~ctx.r11.u32 + ctx.r11.u32 + ctx.xer.ca < ctx.xer.ca);
	ctx.r11.u64 = ~ctx.r11.u64 + ctx.r11.u64 + ctx.xer.ca;
	ctx.xer.ca = temp.u8;
	// rlwinm r11,r11,0,0,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// rlwinm r11,r11,0,26,24
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFFFFFFFFBF;
	// addi r11,r11,96
	ctx.r11.s64 = ctx.r11.s64 + 96;
	// b 0x92249250
	goto loc_92249250;
loc_92249230:
	// subf r11,r5,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r5.u64;
	// lwz r9,52(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 52);
	// lwz r4,44(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 44);
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// lwzx r9,r11,r9
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r9.u32);
	// lwzx r11,r11,r4
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r4.u32);
	// stw r11,-364(r1)
	REX_STORE_U32(ctx.r1.u32 + -364, ctx.r11.u32);
	// addi r11,r9,80
	ctx.r11.s64 = ctx.r9.s64 + 80;
loc_92249250:
	// subf r9,r30,r17
	ctx.r9.u64 = ctx.r17.u64 - ctx.r30.u64;
	// stb r11,-368(r1)
	REX_STORE_U8(ctx.r1.u32 + -368, ctx.r11.u8);
	// srw r11,r26,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r26.u32 >> (ctx.r30.u8 & 0x3F));
	// cmplw cr6,r11,r23
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r23.u32, ctx.xer);
	// slw r4,r10,r9
	ctx.r4.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r9.u8 & 0x3F));
	// bge cr6,0x9224928c
	if (!ctx.cr6.lt) goto loc_9224928C;
	// rlwinm r9,r11,3,0,28
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// rlwinm r3,r4,3,0,28
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 3) & 0xFFFFFFF8;
	// add r9,r9,r31
	ctx.r9.u64 = ctx.r9.u64 + ctx.r31.u64;
loc_92249274:
	// ld r29,-368(r1)
	ctx.r29.u64 = REX_LOAD_U64(ctx.r1.u32 + -368);
	// add r11,r4,r11
	ctx.r11.u64 = ctx.r4.u64 + ctx.r11.u64;
	// cmplw cr6,r11,r23
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r23.u32, ctx.xer);
	// std r29,0(r9)
	REX_STORE_U64(ctx.r9.u32 + 0, ctx.r29.u64);
	// add r9,r3,r9
	ctx.r9.u64 = ctx.r3.u64 + ctx.r9.u64;
	// blt cr6,0x92249274
	if (ctx.cr6.lt) goto loc_92249274;
loc_9224928C:
	// slw r11,r10,r16
	ctx.r11.u64 = ctx.r16.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r16.u8 & 0x3F));
	// b 0x92249298
	goto loc_92249298;
loc_92249294:
	// rlwinm r11,r11,31,1,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 31) & 0x7FFFFFFF;
loc_92249298:
	// and. r9,r11,r26
	ctx.r9.u64 = ctx.r11.u64 & ctx.r26.u64;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// xor r26,r11,r26
	ctx.r26.u64 = ctx.r11.u64 ^ ctx.r26.u64;
	// bne 0x92249294
	if (!ctx.cr0.eq) goto loc_92249294;
	// rlwinm r9,r24,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r24.u32 | (ctx.r24.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r4,r1,-288
	ctx.r4.s64 = ctx.r1.s64 + -288;
	// add r11,r9,r4
	ctx.r11.u64 = ctx.r9.u64 + ctx.r4.u64;
	// b 0x922492c0
	goto loc_922492C0;
loc_922492B4:
	// subf r30,r22,r30
	ctx.r30.u64 = ctx.r30.u64 - ctx.r22.u64;
	// addi r11,r11,-4
	ctx.r11.s64 = ctx.r11.s64 + -4;
	// addi r24,r24,-1
	ctx.r24.s64 = ctx.r24.s64 + -1;
loc_922492C0:
	// slw r9,r10,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// lwz r4,0(r11)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r9,r9,-1
	ctx.r9.s64 = ctx.r9.s64 + -1;
	// and r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 & ctx.r26.u64;
	// cmplw cr6,r9,r4
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r4.u32, ctx.xer);
	// bne cr6,0x922492b4
	if (!ctx.cr6.eq) goto loc_922492B4;
	// cmplwi cr6,r21,0
	ctx.cr6.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// bne cr6,0x922490d0
	if (!ctx.cr6.eq) goto loc_922490D0;
loc_922492E0:
	// addi r17,r17,1
	ctx.r17.s64 = ctx.r17.s64 + 1;
	// addi r19,r19,4
	ctx.r19.s64 = ctx.r19.s64 + 4;
	// addi r16,r16,1
	ctx.r16.s64 = ctx.r16.s64 + 1;
	// cmpw cr6,r17,r7
	ctx.cr6.compare<int32_t>(ctx.r17.s32, ctx.r7.s32, ctx.xer);
	// ble cr6,0x922490c4
	if (!ctx.cr6.gt) goto loc_922490C4;
loc_922492F4:
	// cmpwi cr6,r8,0
	ctx.cr6.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// beq cr6,0x92249308
	if (ctx.cr6.eq) goto loc_92249308;
	// cmpwi cr6,r7,1
	ctx.cr6.compare<int32_t>(ctx.r7.s32, 1, ctx.xer);
	// li r3,-5
	ctx.r3.s64 = -5;
	// bne cr6,0x9224930c
	if (!ctx.cr6.eq) goto loc_9224930C;
loc_92249308:
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
loc_9224930C:
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
loc_92249310:
	// li r3,-4
	ctx.r3.s64 = -4;
	// b 0x9224930c
	goto loc_9224930C;
}

DEFINE_REX_FUNC(sub_92249318) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b470
	ctx.lr = 0x92249320;
	__savegprlr_26(ctx, base);
	// stwu r1,-160(r1)
	ea = -160 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r7
	ctx.r31.u64 = ctx.r7.u64;
	// li r10,0
	ctx.r10.s64 = 0;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r29,r4
	ctx.r29.u64 = ctx.r4.u64;
	// mr r28,r5
	ctx.r28.u64 = ctx.r5.u64;
	// lwz r11,32(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 32);
	// mr r27,r6
	ctx.r27.u64 = ctx.r6.u64;
	// lwz r3,40(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// li r5,4
	ctx.r5.s64 = 4;
	// stw r10,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r10.u32);
	// li r4,19
	ctx.r4.s64 = 19;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249358;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr. r26,r3
	ctx.r26.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r26.s32, 0, ctx.xer);
	// bne 0x92249368
	if (!ctx.cr0.eq) goto loc_92249368;
	// li r3,-4
	ctx.r3.s64 = -4;
	// b 0x922493ec
	goto loc_922493EC;
loc_92249368:
	// addi r11,r1,96
	ctx.r11.s64 = ctx.r1.s64 + 96;
	// stw r26,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r26.u32);
	// mr r10,r27
	ctx.r10.u64 = ctx.r27.u64;
	// mr r9,r29
	ctx.r9.u64 = ctx.r29.u64;
	// mr r8,r28
	ctx.r8.u64 = ctx.r28.u64;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// li r5,19
	ctx.r5.s64 = 19;
	// li r4,19
	ctx.r4.s64 = 19;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92248ea0
	ctx.lr = 0x92249398;
	sub_92248EA0(ctx, base);
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// cmpwi cr6,r30,-3
	ctx.cr6.compare<int32_t>(ctx.r30.s32, -3, ctx.xer);
	// bne cr6,0x922493b0
	if (!ctx.cr6.eq) goto loc_922493B0;
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,20532
	ctx.r11.s64 = ctx.r11.s64 + 20532;
	// b 0x922493d0
	goto loc_922493D0;
loc_922493B0:
	// cmpwi cr6,r30,-5
	ctx.cr6.compare<int32_t>(ctx.r30.s32, -5, ctx.xer);
	// beq cr6,0x922493c4
	if (ctx.cr6.eq) goto loc_922493C4;
	// lwz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x922493d4
	if (!ctx.cr6.eq) goto loc_922493D4;
loc_922493C4:
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// li r30,-3
	ctx.r30.s64 = -3;
	// addi r11,r11,20496
	ctx.r11.s64 = ctx.r11.s64 + 20496;
loc_922493D0:
	// stw r11,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r11.u32);
loc_922493D4:
	// lwz r3,40(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// lwz r11,36(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x922493E8;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
loc_922493EC:
	// addi r1,r1,160
	ctx.r1.s64 = ctx.r1.s64 + 160;
	// b 0x9205b4c0
	__restgprlr_26(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_922493F8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b45c
	ctx.lr = 0x92249400;
	__savegprlr_21(ctx, base);
	// stwu r1,-208(r1)
	ea = -208 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r28,r10
	ctx.r28.u64 = ctx.r10.u64;
	// lwz r27,292(r1)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r1.u32 + 292);
	// li r10,0
	ctx.r10.s64 = 0;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r22,r4
	ctx.r22.u64 = ctx.r4.u64;
	// mr r29,r5
	ctx.r29.u64 = ctx.r5.u64;
	// lwz r11,32(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 32);
	// mr r24,r6
	ctx.r24.u64 = ctx.r6.u64;
	// lwz r3,40(r27)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r27.u32 + 40);
	// mr r23,r7
	ctx.r23.u64 = ctx.r7.u64;
	// mr r26,r8
	ctx.r26.u64 = ctx.r8.u64;
	// stw r10,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r10.u32);
	// mr r21,r9
	ctx.r21.u64 = ctx.r9.u64;
	// li r5,4
	ctx.r5.s64 = 4;
	// li r4,288
	ctx.r4.s64 = 288;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249448;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr. r25,r3
	ctx.r25.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r25.s32, 0, ctx.xer);
	// bne 0x92249458
	if (!ctx.cr0.eq) goto loc_92249458;
	// li r3,-4
	ctx.r3.s64 = -4;
	// b 0x922495b0
	goto loc_922495B0;
loc_92249458:
	// addi r6,r1,96
	ctx.r6.s64 = ctx.r1.s64 + 96;
	// stw r25,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r25.u32);
	// lis r11,-28156
	ctx.r11.s64 = -1845231616;
	// mr r10,r28
	ctx.r10.u64 = ctx.r28.u64;
	// addi r31,r11,3576
	ctx.r31.s64 = ctx.r11.s64 + 3576;
	// mr r9,r24
	ctx.r9.u64 = ctx.r24.u64;
	// stw r6,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r6.u32);
	// addi r7,r31,128
	ctx.r7.s64 = ctx.r31.s64 + 128;
	// mr r8,r26
	ctx.r8.u64 = ctx.r26.u64;
	// mr r6,r31
	ctx.r6.u64 = ctx.r31.u64;
	// li r5,257
	ctx.r5.s64 = 257;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x92248ea0
	ctx.lr = 0x92249490;
	sub_92248EA0(ctx, base);
	// mr. r26,r3
	ctx.r26.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r26.s32, 0, ctx.xer);
	// bne 0x9224956c
	if (!ctx.cr0.eq) goto loc_9224956C;
	// lwz r11,0(r24)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r24.u32 + 0);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x92249588
	if (ctx.cr6.eq) goto loc_92249588;
	// addi r8,r1,96
	ctx.r8.s64 = ctx.r1.s64 + 96;
	// stw r25,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r25.u32);
	// rlwinm r11,r30,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r7,r31,376
	ctx.r7.s64 = ctx.r31.s64 + 376;
	// addi r6,r31,256
	ctx.r6.s64 = ctx.r31.s64 + 256;
	// mr r10,r28
	ctx.r10.u64 = ctx.r28.u64;
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// mr r9,r23
	ctx.r9.u64 = ctx.r23.u64;
	// mr r8,r21
	ctx.r8.u64 = ctx.r21.u64;
	// li r5,0
	ctx.r5.s64 = 0;
	// mr r4,r22
	ctx.r4.u64 = ctx.r22.u64;
	// add r3,r11,r29
	ctx.r3.u64 = ctx.r11.u64 + ctx.r29.u64;
	// bl 0x92248ea0
	ctx.lr = 0x922494D8;
	sub_92248EA0(ctx, base);
	// mr. r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// bne 0x92249510
	if (!ctx.cr0.eq) goto loc_92249510;
	// lwz r11,0(r23)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r23.u32 + 0);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x922494f4
	if (!ctx.cr6.eq) goto loc_922494F4;
	// cmplwi cr6,r30,257
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 257, ctx.xer);
	// bgt cr6,0x92249540
	if (ctx.cr6.gt) goto loc_92249540;
loc_922494F4:
	// lwz r3,40(r27)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r27.u32 + 40);
	// mr r4,r25
	ctx.r4.u64 = ctx.r25.u64;
	// lwz r11,36(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249508;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// li r3,0
	ctx.r3.s64 = 0;
	// b 0x922495b0
	goto loc_922495B0;
loc_92249510:
	// cmpwi cr6,r31,-3
	ctx.cr6.compare<int32_t>(ctx.r31.s32, -3, ctx.xer);
	// bne cr6,0x92249524
	if (!ctx.cr6.eq) goto loc_92249524;
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,20704
	ctx.r11.s64 = ctx.r11.s64 + 20704;
	// b 0x9224954c
	goto loc_9224954C;
loc_92249524:
	// cmpwi cr6,r31,-5
	ctx.cr6.compare<int32_t>(ctx.r31.s32, -5, ctx.xer);
	// bne cr6,0x92249538
	if (!ctx.cr6.eq) goto loc_92249538;
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,20676
	ctx.r11.s64 = ctx.r11.s64 + 20676;
	// b 0x92249548
	goto loc_92249548;
loc_92249538:
	// cmpwi cr6,r31,-4
	ctx.cr6.compare<int32_t>(ctx.r31.s32, -4, ctx.xer);
	// beq cr6,0x92249550
	if (ctx.cr6.eq) goto loc_92249550;
loc_92249540:
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,20640
	ctx.r11.s64 = ctx.r11.s64 + 20640;
loc_92249548:
	// li r31,-3
	ctx.r31.s64 = -3;
loc_9224954C:
	// stw r11,24(r27)
	REX_STORE_U32(ctx.r27.u32 + 24, ctx.r11.u32);
loc_92249550:
	// lwz r3,40(r27)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r27.u32 + 40);
	// mr r4,r25
	ctx.r4.u64 = ctx.r25.u64;
	// lwz r11,36(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249564;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// b 0x922495b0
	goto loc_922495B0;
loc_9224956C:
	// cmpwi cr6,r26,-3
	ctx.cr6.compare<int32_t>(ctx.r26.s32, -3, ctx.xer);
	// bne cr6,0x92249580
	if (!ctx.cr6.eq) goto loc_92249580;
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// addi r11,r11,20604
	ctx.r11.s64 = ctx.r11.s64 + 20604;
	// b 0x92249594
	goto loc_92249594;
loc_92249580:
	// cmpwi cr6,r26,-4
	ctx.cr6.compare<int32_t>(ctx.r26.s32, -4, ctx.xer);
	// beq cr6,0x92249598
	if (ctx.cr6.eq) goto loc_92249598;
loc_92249588:
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// li r26,-3
	ctx.r26.s64 = -3;
	// addi r11,r11,20572
	ctx.r11.s64 = ctx.r11.s64 + 20572;
loc_92249594:
	// stw r11,24(r27)
	REX_STORE_U32(ctx.r27.u32 + 24, ctx.r11.u32);
loc_92249598:
	// lwz r3,40(r27)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r27.u32 + 40);
	// mr r4,r25
	ctx.r4.u64 = ctx.r25.u64;
	// lwz r11,36(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 36);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x922495AC;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
loc_922495B0:
	// addi r1,r1,208
	ctx.r1.s64 = ctx.r1.s64 + 208;
	// b 0x9205b4ac
	__restgprlr_21(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_922495B8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r11,r11,-6072
	ctx.r11.s64 = ctx.r11.s64 + -6072;
	// addi r9,r11,8
	ctx.r9.s64 = ctx.r11.s64 + 8;
	// addi r8,r11,4104
	ctx.r8.s64 = ctx.r11.s64 + 4104;
	// lwz r10,0(r11)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// lwz r11,4(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 4);
	// stw r10,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r10.u32);
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r11,0(r4)
	REX_STORE_U32(ctx.r4.u32 + 0, ctx.r11.u32);
	// stw r9,0(r5)
	REX_STORE_U32(ctx.r5.u32 + 0, ctx.r9.u32);
	// stw r8,0(r6)
	REX_STORE_U32(ctx.r6.u32 + 0, ctx.r8.u32);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_922495E8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b470
	ctx.lr = 0x922495F0;
	__savegprlr_26(ctx, base);
	// stwu r1,-144(r1)
	ea = -144 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r29,r4
	ctx.r29.u64 = ctx.r4.u64;
	// mr r26,r5
	ctx.r26.u64 = ctx.r5.u64;
	// lwz r28,48(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 48);
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r27,12(r29)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r29.u32 + 12);
	// cmplw cr6,r28,r11
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r11.u32, ctx.xer);
	// ble cr6,0x92249618
	if (!ctx.cr6.gt) goto loc_92249618;
	// lwz r11,44(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
loc_92249618:
	// subf r30,r28,r11
	ctx.r30.u64 = ctx.r11.u64 - ctx.r28.u64;
	// lwz r11,16(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 16);
	// cmplw cr6,r30,r11
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, ctx.r11.u32, ctx.xer);
	// ble cr6,0x9224962c
	if (!ctx.cr6.gt) goto loc_9224962C;
	// mr r30,r11
	ctx.r30.u64 = ctx.r11.u64;
loc_9224962C:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x92249640
	if (ctx.cr6.eq) goto loc_92249640;
	// cmpwi cr6,r26,-5
	ctx.cr6.compare<int32_t>(ctx.r26.s32, -5, ctx.xer);
	// bne cr6,0x92249640
	if (!ctx.cr6.eq) goto loc_92249640;
	// li r26,0
	ctx.r26.s64 = 0;
loc_92249640:
	// subf r11,r30,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r30.u64;
	// stw r11,16(r29)
	REX_STORE_U32(ctx.r29.u32 + 16, ctx.r11.u32);
	// lwz r11,20(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 20);
	// add r11,r11,r30
	ctx.r11.u64 = ctx.r11.u64 + ctx.r30.u64;
	// stw r11,20(r29)
	REX_STORE_U32(ctx.r29.u32 + 20, ctx.r11.u32);
	// lwz r11,56(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 56);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq 0x9224967c
	if (ctx.cr0.eq) goto loc_9224967C;
	// lwz r3,60(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 60);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249674;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// stw r3,60(r31)
	REX_STORE_U32(ctx.r31.u32 + 60, ctx.r3.u32);
	// stw r3,48(r29)
	REX_STORE_U32(ctx.r29.u32 + 48, ctx.r3.u32);
loc_9224967C:
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224968C;
	sub_9205B680(ctx, base);
	// lwz r10,44(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 44);
	// add r11,r30,r28
	ctx.r11.u64 = ctx.r30.u64 + ctx.r28.u64;
	// add r27,r30,r27
	ctx.r27.u64 = ctx.r30.u64 + ctx.r27.u64;
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bne cr6,0x92249734
	if (!ctx.cr6.eq) goto loc_92249734;
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r28,40(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 40);
	// cmplw cr6,r11,r10
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r10.u32, ctx.xer);
	// bne cr6,0x922496b4
	if (!ctx.cr6.eq) goto loc_922496B4;
	// stw r28,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r28.u32);
loc_922496B4:
	// lwz r10,52(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// lwz r11,16(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 16);
	// subf r30,r28,r10
	ctx.r30.u64 = ctx.r10.u64 - ctx.r28.u64;
	// cmplw cr6,r30,r11
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, ctx.r11.u32, ctx.xer);
	// ble cr6,0x922496cc
	if (!ctx.cr6.gt) goto loc_922496CC;
	// mr r30,r11
	ctx.r30.u64 = ctx.r11.u64;
loc_922496CC:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x922496e0
	if (ctx.cr6.eq) goto loc_922496E0;
	// cmpwi cr6,r26,-5
	ctx.cr6.compare<int32_t>(ctx.r26.s32, -5, ctx.xer);
	// bne cr6,0x922496e0
	if (!ctx.cr6.eq) goto loc_922496E0;
	// li r26,0
	ctx.r26.s64 = 0;
loc_922496E0:
	// lwz r10,20(r29)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r29.u32 + 20);
	// subf r11,r30,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r30.u64;
	// add r10,r10,r30
	ctx.r10.u64 = ctx.r10.u64 + ctx.r30.u64;
	// stw r11,16(r29)
	REX_STORE_U32(ctx.r29.u32 + 16, ctx.r11.u32);
	// stw r10,20(r29)
	REX_STORE_U32(ctx.r29.u32 + 20, ctx.r10.u32);
	// lwz r11,56(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 56);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq 0x9224971c
	if (ctx.cr0.eq) goto loc_9224971C;
	// lwz r3,60(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 60);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x92249714;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// stw r3,60(r31)
	REX_STORE_U32(ctx.r31.u32 + 60, ctx.r3.u32);
	// stw r3,48(r29)
	REX_STORE_U32(ctx.r29.u32 + 48, ctx.r3.u32);
loc_9224971C:
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224972C;
	sub_9205B680(ctx, base);
	// add r27,r30,r27
	ctx.r27.u64 = ctx.r30.u64 + ctx.r27.u64;
	// add r11,r30,r28
	ctx.r11.u64 = ctx.r30.u64 + ctx.r28.u64;
loc_92249734:
	// stw r27,12(r29)
	REX_STORE_U32(ctx.r29.u32 + 12, ctx.r27.u32);
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// stw r11,48(r31)
	REX_STORE_U32(ctx.r31.u32 + 48, ctx.r11.u32);
	// addi r1,r1,144
	ctx.r1.s64 = ctx.r1.s64 + 144;
	// b 0x9205b4c0
	__restgprlr_26(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92249748) {
	REX_FUNC_PROLOGUE();
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b460
	ctx.lr = 0x92249750;
	__savegprlr_22(ctx, base);
	// lwz r11,48(r7)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r7.u32 + 48);
	// lwz r31,52(r7)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r7.u32 + 52);
	// lwz r24,0(r8)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r8.u32 + 0);
	// lwz r25,4(r8)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r8.u32 + 4);
	// cmplw cr6,r31,r11
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r11.u32, ctx.xer);
	// lwz r29,32(r7)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r7.u32 + 32);
	// lwz r30,28(r7)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r7.u32 + 28);
	// bge cr6,0x9224977c
	if (!ctx.cr6.lt) goto loc_9224977C;
	// subf r11,r31,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r31.u64;
	// addi r26,r11,-1
	ctx.r26.s64 = ctx.r11.s64 + -1;
	// b 0x92249784
	goto loc_92249784;
loc_9224977C:
	// lwz r11,44(r7)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r7.u32 + 44);
	// subf r26,r31,r11
	ctx.r26.u64 = ctx.r11.u64 - ctx.r31.u64;
loc_92249784:
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// rlwinm r10,r4,2,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 2) & 0xFFFFFFFC;
	// addi r27,r11,-1712
	ctx.r27.s64 = ctx.r11.s64 + -1712;
	// rlwinm r11,r3,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r3.u32 | (ctx.r3.u64 << 32), 2) & 0xFFFFFFFC;
	// lwzx r23,r10,r27
	ctx.r23.u64 = REX_LOAD_U32(ctx.r10.u32 + ctx.r27.u32);
	// lwzx r22,r11,r27
	ctx.r22.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r27.u32);
	// b 0x922497b8
	goto loc_922497B8;
loc_922497A0:
	// lbz r11,0(r24)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r24.u32 + 0);
	// addi r25,r25,-1
	ctx.r25.s64 = ctx.r25.s64 + -1;
	// addi r24,r24,1
	ctx.r24.s64 = ctx.r24.s64 + 1;
	// slw r11,r11,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r30.u8 & 0x3F));
	// addi r30,r30,8
	ctx.r30.s64 = ctx.r30.s64 + 8;
	// or r29,r11,r29
	ctx.r29.u64 = ctx.r11.u64 | ctx.r29.u64;
loc_922497B8:
	// cmplwi cr6,r30,20
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 20, ctx.xer);
	// blt cr6,0x922497a0
	if (ctx.cr6.lt) goto loc_922497A0;
	// and r11,r22,r29
	ctx.r11.u64 = ctx.r22.u64 & ctx.r29.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r9,r11,r5
	ctx.r9.u64 = ctx.r11.u64 + ctx.r5.u64;
	// lbz r4,0(r9)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r9.u32 + 0);
	// lbz r11,1(r9)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r9.u32 + 1);
	// cmplwi r4,0
	ctx.cr0.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne 0x922497f0
	if (!ctx.cr0.eq) goto loc_922497F0;
	// lwz r10,4(r9)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// srw r29,r29,r11
	ctx.r29.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r29.u32 >> (ctx.r11.u8 & 0x3F));
	// subf r30,r11,r30
	ctx.r30.u64 = ctx.r30.u64 - ctx.r11.u64;
	// stb r10,0(r31)
	REX_STORE_U8(ctx.r31.u32 + 0, ctx.r10.u8);
	// b 0x922499c0
	goto loc_922499C0;
loc_922497F0:
	// rlwinm. r10,r4,0,27,27
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x10;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// srw r10,r29,r11
	ctx.r10.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r29.u32 >> (ctx.r11.u8 & 0x3F));
	// subf r11,r11,r30
	ctx.r11.u64 = ctx.r30.u64 - ctx.r11.u64;
	// bne 0x92249844
	if (!ctx.cr0.eq) goto loc_92249844;
loc_92249800:
	// rlwinm. r3,r4,0,25,25
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x40;
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x92249a34
	if (!ctx.cr0.eq) goto loc_92249A34;
	// rlwinm r4,r4,2,0,29
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r3,4(r9)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// lwzx r4,r4,r27
	ctx.r4.u64 = REX_LOAD_U32(ctx.r4.u32 + ctx.r27.u32);
	// and r4,r4,r10
	ctx.r4.u64 = ctx.r4.u64 & ctx.r10.u64;
	// add r4,r4,r3
	ctx.r4.u64 = ctx.r4.u64 + ctx.r3.u64;
	// rlwinm r4,r4,3,0,28
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 3) & 0xFFFFFFF8;
	// add r9,r4,r9
	ctx.r9.u64 = ctx.r4.u64 + ctx.r9.u64;
	// lbz r4,0(r9)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r9.u32 + 0);
	// cmplwi r4,0
	ctx.cr0.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// beq 0x922499ac
	if (ctx.cr0.eq) goto loc_922499AC;
	// lbz r3,1(r9)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r9.u32 + 1);
	// rlwinm. r30,r4,0,27,27
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x10;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// subf r11,r3,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r3.u64;
	// srw r10,r10,r3
	ctx.r10.u64 = ctx.r3.u8 & 0x20 ? 0 : (ctx.r10.u32 >> (ctx.r3.u8 & 0x3F));
	// beq 0x92249800
	if (ctx.cr0.eq) goto loc_92249800;
loc_92249844:
	// clrlwi r4,r4,28
	ctx.r4.u64 = ctx.r4.u32 & 0xF;
	// lwz r3,4(r9)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// rlwinm r9,r4,2,0,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 2) & 0xFFFFFFFC;
	// subf r11,r4,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r4.u64;
	// lwzx r9,r9,r27
	ctx.r9.u64 = REX_LOAD_U32(ctx.r9.u32 + ctx.r27.u32);
	// and r9,r9,r10
	ctx.r9.u64 = ctx.r9.u64 & ctx.r10.u64;
	// add r28,r9,r3
	ctx.r28.u64 = ctx.r9.u64 + ctx.r3.u64;
	// srw r10,r10,r4
	ctx.r10.u64 = ctx.r4.u8 & 0x20 ? 0 : (ctx.r10.u32 >> (ctx.r4.u8 & 0x3F));
	// b 0x92249880
	goto loc_92249880;
loc_92249868:
	// lbz r9,0(r24)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r24.u32 + 0);
	// addi r25,r25,-1
	ctx.r25.s64 = ctx.r25.s64 + -1;
	// addi r24,r24,1
	ctx.r24.s64 = ctx.r24.s64 + 1;
	// slw r9,r9,r11
	ctx.r9.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r11.u8 & 0x3F));
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// or r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 | ctx.r10.u64;
loc_92249880:
	// cmplwi cr6,r11,15
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 15, ctx.xer);
	// blt cr6,0x92249868
	if (ctx.cr6.lt) goto loc_92249868;
	// and r9,r23,r10
	ctx.r9.u64 = ctx.r23.u64 & ctx.r10.u64;
	// rlwinm r9,r9,3,0,28
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 3) & 0xFFFFFFF8;
	// add r9,r9,r6
	ctx.r9.u64 = ctx.r9.u64 + ctx.r6.u64;
	// b 0x922498bc
	goto loc_922498BC;
loc_92249898:
	// rlwinm. r3,r4,0,25,25
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x40;
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x92249a28
	if (!ctx.cr0.eq) goto loc_92249A28;
	// rlwinm r4,r4,2,0,29
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r3,4(r9)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// lwzx r4,r4,r27
	ctx.r4.u64 = REX_LOAD_U32(ctx.r4.u32 + ctx.r27.u32);
	// and r4,r4,r10
	ctx.r4.u64 = ctx.r4.u64 & ctx.r10.u64;
	// add r4,r4,r3
	ctx.r4.u64 = ctx.r4.u64 + ctx.r3.u64;
	// rlwinm r4,r4,3,0,28
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 3) & 0xFFFFFFF8;
	// add r9,r4,r9
	ctx.r9.u64 = ctx.r4.u64 + ctx.r9.u64;
loc_922498BC:
	// lbz r3,1(r9)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r9.u32 + 1);
	// lbz r4,0(r9)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r9.u32 + 0);
	// subf r11,r3,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r3.u64;
	// srw r10,r10,r3
	ctx.r10.u64 = ctx.r3.u8 & 0x20 ? 0 : (ctx.r10.u32 >> (ctx.r3.u8 & 0x3F));
	// rlwinm. r30,r4,0,27,27
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x10;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// beq 0x92249898
	if (ctx.cr0.eq) goto loc_92249898;
	// clrlwi r4,r4,28
	ctx.r4.u64 = ctx.r4.u32 & 0xF;
	// b 0x922498f4
	goto loc_922498F4;
loc_922498DC:
	// lbz r3,0(r24)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r24.u32 + 0);
	// addi r25,r25,-1
	ctx.r25.s64 = ctx.r25.s64 + -1;
	// addi r24,r24,1
	ctx.r24.s64 = ctx.r24.s64 + 1;
	// slw r3,r3,r11
	ctx.r3.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r3.u32 << (ctx.r11.u8 & 0x3F));
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// or r10,r3,r10
	ctx.r10.u64 = ctx.r3.u64 | ctx.r10.u64;
loc_922498F4:
	// cmplw cr6,r11,r4
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r4.u32, ctx.xer);
	// blt cr6,0x922498dc
	if (ctx.cr6.lt) goto loc_922498DC;
	// rlwinm r3,r4,2,0,29
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r9,4(r9)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// subf r30,r4,r11
	ctx.r30.u64 = ctx.r11.u64 - ctx.r4.u64;
	// srw r29,r10,r4
	ctx.r29.u64 = ctx.r4.u8 & 0x20 ? 0 : (ctx.r10.u32 >> (ctx.r4.u8 & 0x3F));
	// subf r26,r28,r26
	ctx.r26.u64 = ctx.r26.u64 - ctx.r28.u64;
	// lwzx r11,r3,r27
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + ctx.r27.u32);
	// and r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 & ctx.r10.u64;
	// lwz r10,40(r7)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r7.u32 + 40);
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// subf r9,r10,r31
	ctx.r9.u64 = ctx.r31.u64 - ctx.r10.u64;
	// cmplw cr6,r9,r11
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x92249958
	if (ctx.cr6.lt) goto loc_92249958;
	// subf r11,r11,r31
	ctx.r11.u64 = ctx.r31.u64 - ctx.r11.u64;
	// addi r9,r31,1
	ctx.r9.s64 = ctx.r31.s64 + 1;
	// addi r28,r28,-2
	ctx.r28.s64 = ctx.r28.s64 + -2;
	// lbz r10,0(r11)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stb r10,0(r31)
	REX_STORE_U8(ctx.r31.u32 + 0, ctx.r10.u8);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r4,0(r11)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r31,r9,1
	ctx.r31.s64 = ctx.r9.s64 + 1;
	// stb r4,0(r9)
	REX_STORE_U8(ctx.r9.u32 + 0, ctx.r4.u8);
	// b 0x92249990
	goto loc_92249990;
loc_92249958:
	// subf r10,r31,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r31.u64;
	// lwz r9,44(r7)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r7.u32 + 44);
	// add r11,r10,r11
	ctx.r11.u64 = ctx.r10.u64 + ctx.r11.u64;
	// subf r10,r11,r9
	ctx.r10.u64 = ctx.r9.u64 - ctx.r11.u64;
	// cmplw cr6,r28,r11
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r11.u32, ctx.xer);
	// ble cr6,0x92249990
	if (!ctx.cr6.gt) goto loc_92249990;
	// subf r28,r11,r28
	ctx.r28.u64 = ctx.r28.u64 - ctx.r11.u64;
loc_92249974:
	// lbz r9,0(r10)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// stb r9,0(r31)
	REX_STORE_U8(ctx.r31.u32 + 0, ctx.r9.u8);
	// addi r31,r31,1
	ctx.r31.s64 = ctx.r31.s64 + 1;
	// bne 0x92249974
	if (!ctx.cr0.eq) goto loc_92249974;
	// lwz r10,40(r7)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r7.u32 + 40);
loc_92249990:
	// lbz r11,0(r10)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// addic. r28,r28,-1
	ctx.xer.ca = ctx.r28.u32 > 0;
	ctx.r28.s64 = ctx.r28.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r28.s32, 0, ctx.xer);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// stb r11,0(r31)
	REX_STORE_U8(ctx.r31.u32 + 0, ctx.r11.u8);
	// addi r31,r31,1
	ctx.r31.s64 = ctx.r31.s64 + 1;
	// bne 0x92249990
	if (!ctx.cr0.eq) goto loc_92249990;
	// b 0x922499c8
	goto loc_922499C8;
loc_922499AC:
	// lbz r4,1(r9)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r9.u32 + 1);
	// lwz r9,4(r9)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r9.u32 + 4);
	// subf r30,r4,r11
	ctx.r30.u64 = ctx.r11.u64 - ctx.r4.u64;
	// stb r9,0(r31)
	REX_STORE_U8(ctx.r31.u32 + 0, ctx.r9.u8);
	// srw r29,r10,r4
	ctx.r29.u64 = ctx.r4.u8 & 0x20 ? 0 : (ctx.r10.u32 >> (ctx.r4.u8 & 0x3F));
loc_922499C0:
	// addi r31,r31,1
	ctx.r31.s64 = ctx.r31.s64 + 1;
	// addi r26,r26,-1
	ctx.r26.s64 = ctx.r26.s64 + -1;
loc_922499C8:
	// cmplwi cr6,r26,258
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 258, ctx.xer);
	// blt cr6,0x922499d8
	if (ctx.cr6.lt) goto loc_922499D8;
	// cmplwi cr6,r25,10
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 10, ctx.xer);
	// bge cr6,0x922497b8
	if (!ctx.cr6.lt) goto loc_922497B8;
loc_922499D8:
	// lwz r11,4(r8)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r8.u32 + 4);
	// rlwinm r10,r30,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 29) & 0x1FFFFFFF;
	// subf r11,r25,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r25.u64;
	// cmplw cr6,r10,r11
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r11.u32, ctx.xer);
	// bge cr6,0x922499f0
	if (!ctx.cr6.lt) goto loc_922499F0;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
loc_922499F0:
	// rlwinm r9,r11,3,0,28
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// stw r29,32(r7)
	REX_STORE_U32(ctx.r7.u32 + 32, ctx.r29.u32);
	// subf r10,r11,r24
	ctx.r10.u64 = ctx.r24.u64 - ctx.r11.u64;
	// subf r9,r9,r30
	ctx.r9.u64 = ctx.r30.u64 - ctx.r9.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r9,28(r7)
	REX_STORE_U32(ctx.r7.u32 + 28, ctx.r9.u32);
	// stw r11,4(r8)
	REX_STORE_U32(ctx.r8.u32 + 4, ctx.r11.u32);
	// lwz r9,0(r8)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r8.u32 + 0);
	// lwz r11,8(r8)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r8.u32 + 8);
	// stw r10,0(r8)
	REX_STORE_U32(ctx.r8.u32 + 0, ctx.r10.u32);
	// subf r11,r9,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r9.u64;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// b 0x92249ab4
	goto loc_92249AB4;
loc_92249A28:
	// lis r9,-28157
	ctx.r9.s64 = -1845297152;
	// addi r5,r9,19976
	ctx.r5.s64 = ctx.r9.s64 + 19976;
	// b 0x92249a64
	goto loc_92249A64;
loc_92249A34:
	// rlwinm. r9,r4,0,26,26
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r4.u32 | (ctx.r4.u64 << 32), 0) & 0x20;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x92249a5c
	if (ctx.cr0.eq) goto loc_92249A5C;
	// lwz r9,4(r8)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r8.u32 + 4);
	// rlwinm r6,r11,29,3,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// subf r9,r25,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r25.u64;
	// cmplw cr6,r6,r9
	ctx.cr6.compare<uint32_t>(ctx.r6.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x92249a54
	if (!ctx.cr6.lt) goto loc_92249A54;
	// mr r9,r6
	ctx.r9.u64 = ctx.r6.u64;
loc_92249A54:
	// li r3,1
	ctx.r3.s64 = 1;
	// b 0x92249a84
	goto loc_92249A84;
loc_92249A5C:
	// lis r9,-28157
	ctx.r9.s64 = -1845297152;
	// addi r5,r9,19948
	ctx.r5.s64 = ctx.r9.s64 + 19948;
loc_92249A64:
	// lwz r4,4(r8)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r8.u32 + 4);
	// rlwinm r6,r11,29,3,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// stw r5,24(r8)
	REX_STORE_U32(ctx.r8.u32 + 24, ctx.r5.u32);
	// subf r9,r25,r4
	ctx.r9.u64 = ctx.r4.u64 - ctx.r25.u64;
	// cmplw cr6,r6,r9
	ctx.cr6.compare<uint32_t>(ctx.r6.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x92249a80
	if (!ctx.cr6.lt) goto loc_92249A80;
	// mr r9,r6
	ctx.r9.u64 = ctx.r6.u64;
loc_92249A80:
	// li r3,-3
	ctx.r3.s64 = -3;
loc_92249A84:
	// rlwinm r5,r9,3,0,28
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 3) & 0xFFFFFFF8;
	// stw r10,32(r7)
	REX_STORE_U32(ctx.r7.u32 + 32, ctx.r10.u32);
	// subf r6,r9,r24
	ctx.r6.u64 = ctx.r24.u64 - ctx.r9.u64;
	// subf r11,r5,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r5.u64;
	// add r9,r9,r25
	ctx.r9.u64 = ctx.r9.u64 + ctx.r25.u64;
	// stw r11,28(r7)
	REX_STORE_U32(ctx.r7.u32 + 28, ctx.r11.u32);
	// lwz r11,0(r8)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r8.u32 + 0);
	// lwz r10,8(r8)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r8.u32 + 8);
	// stw r9,4(r8)
	REX_STORE_U32(ctx.r8.u32 + 4, ctx.r9.u32);
	// subf r11,r11,r10
	ctx.r11.u64 = ctx.r10.u64 - ctx.r11.u64;
	// stw r6,0(r8)
	REX_STORE_U32(ctx.r8.u32 + 0, ctx.r6.u32);
	// add r11,r11,r6
	ctx.r11.u64 = ctx.r11.u64 + ctx.r6.u64;
loc_92249AB4:
	// stw r11,8(r8)
	REX_STORE_U32(ctx.r8.u32 + 8, ctx.r11.u32);
	// stw r31,52(r7)
	REX_STORE_U32(ctx.r7.u32 + 52, ctx.r31.u32);
	// b 0x9205b4b0
	__restgprlr_22(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92249AC0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b464
	ctx.lr = 0x92249AC8;
	__savegprlr_23(ctx, base);
	// stwu r1,-272(r1)
	ea = -272 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r28,r8
	ctx.r28.u64 = ctx.r8.u64;
	// mr r27,r3
	ctx.r27.u64 = ctx.r3.u64;
	// mr r26,r4
	ctx.r26.u64 = ctx.r4.u64;
	// mr r25,r5
	ctx.r25.u64 = ctx.r5.u64;
	// addi r5,r1,128
	ctx.r5.s64 = ctx.r1.s64 + 128;
	// addi r4,r1,132
	ctx.r4.s64 = ctx.r1.s64 + 132;
	// clrlwi r3,r28,26
	ctx.r3.u64 = ctx.r28.u32 & 0x3F;
	// mr r29,r6
	ctx.r29.u64 = ctx.r6.u64;
	// mr r30,r7
	ctx.r30.u64 = ctx.r7.u64;
	// mr r23,r9
	ctx.r23.u64 = ctx.r9.u64;
	// mr r24,r10
	ctx.r24.u64 = ctx.r10.u64;
	// bl 0x92092280
	ctx.lr = 0x92249AFC;
	sub_92092280(ctx, base);
	// lwz r3,388(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 388);
	// li r31,0
	ctx.r31.s64 = 0;
	// cmplwi cr6,r29,1
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 1, ctx.xer);
	// beq cr6,0x92249b54
	if (ctx.cr6.eq) goto loc_92249B54;
	// cmplwi cr6,r29,0
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 0, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmplwi cr6,r27,1
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, 1, ctx.xer);
	// bne cr6,0x92249b34
	if (!ctx.cr6.eq) goto loc_92249B34;
	// cmplwi cr6,r26,1
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 1, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmplwi cr6,r25,1
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 1, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmpwi cr6,r24,0
	ctx.cr6.compare<int32_t>(ctx.r24.s32, 0, ctx.xer);
	// beq cr6,0x92249b54
	if (ctx.cr6.eq) goto loc_92249B54;
loc_92249B34:
	// cmplwi cr6,r27,3
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, 3, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmplwi cr6,r26,3
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 3, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmplwi cr6,r25,3
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 3, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// cmpwi cr6,r24,0
	ctx.cr6.compare<int32_t>(ctx.r24.s32, 0, ctx.xer);
	// beq cr6,0x92249b70
	if (ctx.cr6.eq) goto loc_92249B70;
loc_92249B54:
	// cmpwi cr6,r3,3
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 3, ctx.xer);
	// bne cr6,0x92249b70
	if (!ctx.cr6.eq) goto loc_92249B70;
	// lwz r10,128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// lwz r11,380(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 380);
	// twllei r10,0
	if (ctx.r10.s32 == 0 || ctx.r10.u32 < 0u) ppc_trap(ctx, base, 0);
	// divwu r10,r11,r10
	ctx.r10.u64 = uint32_t(ctx.r10.u32 ? ctx.r11.u32 / ctx.r10.u32 : 0);
	// b 0x92249b74
	goto loc_92249B74;
loc_92249B70:
	// mr r10,r31
	ctx.r10.u64 = ctx.r31.u64;
loc_92249B74:
	// addi r11,r1,144
	ctx.r11.s64 = ctx.r1.s64 + 144;
	// stw r10,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r10.u32);
	// lwz r10,356(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 356);
	// addi r7,r1,132
	ctx.r7.s64 = ctx.r1.s64 + 132;
	// addi r6,r1,128
	ctx.r6.s64 = ctx.r1.s64 + 128;
	// stw r24,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r24.u32);
	// addi r5,r1,144
	ctx.r5.s64 = ctx.r1.s64 + 144;
	// mr r9,r28
	ctx.r9.u64 = ctx.r28.u64;
	// std r31,0(r11)
	REX_STORE_U64(ctx.r11.u32 + 0, ctx.r31.u64);
	// mr r8,r30
	ctx.r8.u64 = ctx.r30.u64;
	// std r31,8(r11)
	REX_STORE_U64(ctx.r11.u32 + 8, ctx.r31.u64);
	// mr r4,r27
	ctx.r4.u64 = ctx.r27.u64;
	// std r31,16(r11)
	REX_STORE_U64(ctx.r11.u32 + 16, ctx.r31.u64);
	// stw r10,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r10.u32);
	// mr r10,r23
	ctx.r10.u64 = ctx.r23.u64;
	// stw r7,124(r1)
	REX_STORE_U32(ctx.r1.u32 + 124, ctx.r7.u32);
	// mr r7,r29
	ctx.r7.u64 = ctx.r29.u64;
	// stw r6,116(r1)
	REX_STORE_U32(ctx.r1.u32 + 116, ctx.r6.u32);
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// stw r5,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r5.u32);
	// mr r5,r26
	ctx.r5.u64 = ctx.r26.u64;
	// std r31,24(r11)
	REX_STORE_U64(ctx.r11.u32 + 24, ctx.r31.u64);
	// std r31,32(r11)
	REX_STORE_U64(ctx.r11.u32 + 32, ctx.r31.u64);
	// bl 0x920936e8
	ctx.lr = 0x92249BD4;
	sub_920936E8(ctx, base);
	// lis r11,3
	ctx.r11.s64 = 196608;
	// lwz r9,164(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 164);
	// ori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 | 1;
	// lwz r10,364(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 364);
	// rlwimi r9,r10,0,0,19
	ctx.r9.u64 = (__builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFF000) | (ctx.r9.u64 & 0xFFFFFFFF00000FFF);
	// stw r11,144(r1)
	REX_STORE_U32(ctx.r1.u32 + 144, ctx.r11.u32);
	// lis r11,-1
	ctx.r11.s64 = -65536;
	// stw r9,164(r1)
	REX_STORE_U32(ctx.r1.u32 + 164, ctx.r9.u32);
	// stw r11,152(r1)
	REX_STORE_U32(ctx.r1.u32 + 152, ctx.r11.u32);
	// stw r11,156(r1)
	REX_STORE_U32(ctx.r1.u32 + 156, ctx.r11.u32);
	// rlwinm. r8,r30,0,29,29
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 0) & 0x4;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// beq 0x92249c10
	if (ctx.cr0.eq) goto loc_92249C10;
	// lis r11,16387
	ctx.r11.s64 = 1073938432;
	// ori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 | 1;
	// stw r11,144(r1)
	REX_STORE_U32(ctx.r1.u32 + 144, ctx.r11.u32);
loc_92249C10:
	// lwz r7,132(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 132);
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// beq cr6,0x92249c58
	if (ctx.cr6.eq) goto loc_92249C58;
	// lwz r11,372(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 372);
	// cmpwi cr6,r11,-1
	ctx.cr6.compare<int32_t>(ctx.r11.s32, -1, ctx.xer);
	// bne cr6,0x92249c44
	if (!ctx.cr6.eq) goto loc_92249C44;
	// lwz r11,128(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// lwz r9,180(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 180);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r8,r11,0,0,19
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// add r11,r8,r10
	ctx.r11.u64 = ctx.r8.u64 + ctx.r10.u64;
	// rlwimi r11,r9,0,20,31
	ctx.r11.u64 = (__builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 0) & 0xFFF) | (ctx.r11.u64 & 0xFFFFFFFFFFFFF000);
	// b 0x92249c64
	goto loc_92249C64;
loc_92249C44:
	// lwz r10,180(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 180);
	// lwz r8,128(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// rlwimi r10,r11,0,0,19
	ctx.r10.u64 = (__builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000) | (ctx.r10.u64 & 0xFFFFFFFF00000FFF);
	// stw r10,180(r1)
	REX_STORE_U32(ctx.r1.u32 + 180, ctx.r10.u32);
	// b 0x92249c68
	goto loc_92249C68;
loc_92249C58:
	// lwz r11,180(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 180);
	// lwz r8,128(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// clrlwi r11,r11,20
	ctx.r11.u64 = ctx.r11.u32 & 0xFFF;
loc_92249C64:
	// stw r11,180(r1)
	REX_STORE_U32(ctx.r1.u32 + 180, ctx.r11.u32);
loc_92249C68:
	// lwz r11,404(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 404);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x92249c78
	if (ctx.cr6.eq) goto loc_92249C78;
	// stw r8,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r8.u32);
loc_92249C78:
	// lwz r11,412(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 412);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x92249c88
	if (ctx.cr6.eq) goto loc_92249C88;
	// stw r7,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r7.u32);
loc_92249C88:
	// lwz r10,396(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 396);
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// beq cr6,0x92249cb4
	if (ctx.cr6.eq) goto loc_92249CB4;
	// addi r11,r1,144
	ctx.r11.s64 = ctx.r1.s64 + 144;
	// li r9,10
	ctx.r9.s64 = 10;
	// mtctr r9
	ctx.ctr.u64 = ctx.r9.u64;
loc_92249CA0:
	// lwz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// stw r9,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r9.u32);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// bdnz 0x92249ca0
	--ctx.ctr.u64;
	if (ctx.ctr.u32 != 0) goto loc_92249CA0;
loc_92249CB4:
	// add r3,r8,r7
	ctx.r3.u64 = ctx.r8.u64 + ctx.r7.u64;
	// addi r1,r1,272
	ctx.r1.s64 = ctx.r1.s64 + 272;
	// b 0x9205b4b4
	__restgprlr_23(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92249CC0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b47c
	ctx.lr = 0x92249CC8;
	__savegprlr_29(ctx, base);
	// stwu r1,-176(r1)
	ea = -176 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r8,r7
	ctx.r8.u64 = ctx.r7.u64;
	// lwz r29,260(r1)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r1.u32 + 260);
	// mr r7,r10
	ctx.r7.u64 = ctx.r10.u64;
	// lwz r10,284(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 284);
	// mr r11,r9
	ctx.r11.u64 = ctx.r9.u64;
	// lwz r9,268(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 268);
	// li r31,3
	ctx.r31.s64 = 3;
	// li r30,0
	ctx.r30.s64 = 0;
	// stw r29,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r29.u32);
	// stw r10,140(r1)
	REX_STORE_U32(ctx.r1.u32 + 140, ctx.r10.u32);
	// lwz r10,276(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 276);
	// stw r7,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r7.u32);
	// mr r7,r6
	ctx.r7.u64 = ctx.r6.u64;
	// stw r9,124(r1)
	REX_STORE_U32(ctx.r1.u32 + 124, ctx.r9.u32);
	// mr r6,r5
	ctx.r6.u64 = ctx.r5.u64;
	// li r9,2
	ctx.r9.s64 = 2;
	// stw r31,116(r1)
	REX_STORE_U32(ctx.r1.u32 + 116, ctx.r31.u32);
	// li r5,1
	ctx.r5.s64 = 1;
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// stw r10,132(r1)
	REX_STORE_U32(ctx.r1.u32 + 132, ctx.r10.u32);
	// li r10,0
	ctx.r10.s64 = 0;
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// bl 0x92249ac0
	ctx.lr = 0x92249D28;
	sub_92249AC0(ctx, base);
	// addi r1,r1,176
	ctx.r1.s64 = ctx.r1.s64 + 176;
	// b 0x9205b4cc
	__restgprlr_29(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92249D30) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b454
	ctx.lr = 0x92249D38;
	__savegprlr_19(ctx, base);
	// stwu r1,-224(r1)
	ea = -224 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r7
	ctx.r31.u64 = ctx.r7.u64;
	// mr r28,r8
	ctx.r28.u64 = ctx.r8.u64;
	// mr r22,r3
	ctx.r22.u64 = ctx.r3.u64;
	// mr r21,r4
	ctx.r21.u64 = ctx.r4.u64;
	// mr r20,r5
	ctx.r20.u64 = ctx.r5.u64;
	// lwz r11,28(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// mr r19,r6
	ctx.r19.u64 = ctx.r6.u64;
	// lwz r10,20(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 20);
	// addi r6,r1,100
	ctx.r6.s64 = ctx.r1.s64 + 100;
	// rlwinm r30,r11,1,31,31
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x1;
	// lwz r9,16(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 16);
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// clrlwi r27,r10,26
	ctx.r27.u64 = ctx.r10.u32 & 0x3F;
	// lwz r10,36(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// addi r11,r11,18888
	ctx.r11.s64 = ctx.r11.s64 + 18888;
	// rlwinm r8,r27,1,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 1) & 0xFFFFFFFE;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r5,r1,96
	ctx.r5.s64 = ctx.r1.s64 + 96;
	// addi r4,r1,92
	ctx.r4.s64 = ctx.r1.s64 + 92;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// rlwinm r29,r30,1,0,30
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 1) & 0xFFFFFFFE;
	// lbzx r25,r8,r11
	ctx.r25.u64 = REX_LOAD_U8(ctx.r8.u32 + ctx.r11.u32);
	// rlwinm r26,r10,23,30,31
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 23) & 0x3;
	// rlwinm r24,r9,1,31,31
	ctx.r24.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0x1;
	// bl 0x920921b8
	ctx.lr = 0x92249DA0;
	sub_920921B8(ctx, base);
	// lwz r9,92(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// cmplwi cr6,r28,0
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 0, ctx.xer);
	// lwz r8,96(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// subf r10,r29,r9
	ctx.r10.u64 = ctx.r9.u64 - ctx.r29.u64;
	// subf r11,r29,r8
	ctx.r11.u64 = ctx.r8.u64 - ctx.r29.u64;
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// addi r7,r11,-1
	ctx.r7.s64 = ctx.r11.s64 + -1;
	// cntlzw r11,r10
	ctx.r11.u64 = ctx.r10.u32 == 0 ? 32 : __builtin_clz(ctx.r10.u32);
	// cntlzw r10,r7
	ctx.r10.u64 = ctx.r7.u32 == 0 ? 32 : __builtin_clz(ctx.r7.u32);
	// subf r11,r11,r30
	ctx.r11.u64 = ctx.r30.u64 - ctx.r11.u64;
	// subf r10,r10,r30
	ctx.r10.u64 = ctx.r30.u64 - ctx.r10.u64;
	// addi r7,r11,32
	ctx.r7.s64 = ctx.r11.s64 + 32;
	// addi r6,r10,32
	ctx.r6.s64 = ctx.r10.s64 + 32;
	// bne cr6,0x92249e50
	if (!ctx.cr6.eq) goto loc_92249E50;
	// li r10,1
	ctx.r10.s64 = 1;
	// stw r10,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r10.u32);
	// slw r11,r10,r7
	ctx.r11.u64 = ctx.r7.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r7.u8 & 0x3F));
	// slw r7,r10,r6
	ctx.r7.u64 = ctx.r6.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r6.u8 & 0x3F));
	// cmplwi cr6,r11,16
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 16, ctx.xer);
	// stw r11,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
	// stw r7,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r7.u32);
	// ble cr6,0x92249e00
	if (!ctx.cr6.gt) goto loc_92249E00;
	// cmplwi cr6,r7,16
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 16, ctx.xer);
	// bgt cr6,0x92249e14
	if (ctx.cr6.gt) goto loc_92249E14;
loc_92249E00:
	// lwz r11,36(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// rlwinm. r11,r11,0,20,20
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x800;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x92249e14
	if (ctx.cr0.eq) goto loc_92249E14;
	// mr r23,r10
	ctx.r23.u64 = ctx.r10.u64;
	// b 0x92249e24
	goto loc_92249E24;
loc_92249E14:
	// li r23,0
	ctx.r23.s64 = 0;
	// stw r9,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r9.u32);
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// stw r10,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r10.u32);
loc_92249E24:
	// mr r9,r24
	ctx.r9.u64 = ctx.r24.u64;
	// mr r8,r26
	ctx.r8.u64 = ctx.r26.u64;
	// mr r7,r27
	ctx.r7.u64 = ctx.r27.u64;
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// addi r5,r1,88
	ctx.r5.s64 = ctx.r1.s64 + 88;
	// addi r4,r1,84
	ctx.r4.s64 = ctx.r1.s64 + 84;
	// addi r3,r1,80
	ctx.r3.s64 = ctx.r1.s64 + 80;
	// bl 0x92092428
	ctx.lr = 0x92249E44;
	sub_92092428(ctx, base);
	// lwz r11,16(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 16);
	// rlwinm r11,r11,15,18,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 15) & 0x3FE0;
	// b 0x92249f48
	goto loc_92249F48;
loc_92249E50:
	// subf r10,r29,r9
	ctx.r10.u64 = ctx.r9.u64 - ctx.r29.u64;
	// subf r11,r29,r8
	ctx.r11.u64 = ctx.r8.u64 - ctx.r29.u64;
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// addi r9,r11,-1
	ctx.r9.s64 = ctx.r11.s64 + -1;
	// cntlzw r11,r10
	ctx.r11.u64 = ctx.r10.u32 == 0 ? 32 : __builtin_clz(ctx.r10.u32);
	// cntlzw r10,r9
	ctx.r10.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
	// subf r11,r11,r30
	ctx.r11.u64 = ctx.r30.u64 - ctx.r11.u64;
	// subf r10,r10,r30
	ctx.r10.u64 = ctx.r30.u64 - ctx.r10.u64;
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// addi r10,r10,32
	ctx.r10.s64 = ctx.r10.s64 + 32;
	// cmpw cr6,r11,r10
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r10.s32, ctx.xer);
	// blt cr6,0x92249e84
	if (ctx.cr6.lt) goto loc_92249E84;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
loc_92249E84:
	// addic. r11,r11,-4
	ctx.xer.ca = ctx.r11.u32 > 3;
	ctx.r11.s64 = ctx.r11.s64 + -4;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bgt 0x92249e90
	if (ctx.cr0.gt) goto loc_92249E90;
	// li r11,0
	ctx.r11.s64 = 0;
loc_92249E90:
	// li r10,1
	ctx.r10.s64 = 1;
	// cmplw cr6,r28,r11
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x92249ed4
	if (ctx.cr6.lt) goto loc_92249ED4;
	// lwz r9,36(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 36);
	// rlwinm. r9,r9,0,20,20
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 0) & 0x800;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x92249ed4
	if (ctx.cr0.eq) goto loc_92249ED4;
	// mr r23,r10
	ctx.r23.u64 = ctx.r10.u64;
	// mr r28,r11
	ctx.r28.u64 = ctx.r11.u64;
loc_92249EB0:
	// cmplwi cr6,r26,2
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 2, ctx.xer);
	// bne cr6,0x92249edc
	if (!ctx.cr6.eq) goto loc_92249EDC;
	// lwz r11,100(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// subf r11,r29,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r29.u64;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// subf r11,r11,r30
	ctx.r11.u64 = ctx.r30.u64 - ctx.r11.u64;
	// addi r9,r11,32
	ctx.r9.s64 = ctx.r11.s64 + 32;
	// b 0x92249ee0
	goto loc_92249EE0;
loc_92249ED4:
	// li r23,0
	ctx.r23.s64 = 0;
	// b 0x92249eb0
	goto loc_92249EB0;
loc_92249EDC:
	// li r9,0
	ctx.r9.s64 = 0;
loc_92249EE0:
	// subf. r11,r28,r7
	ctx.r11.u64 = ctx.r7.u64 - ctx.r28.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// li r30,0
	ctx.r30.s64 = 0;
	// blt 0x92249ef0
	if (ctx.cr0.lt) goto loc_92249EF0;
	// mr r30,r11
	ctx.r30.u64 = ctx.r11.u64;
loc_92249EF0:
	// subf. r11,r28,r6
	ctx.r11.u64 = ctx.r6.u64 - ctx.r28.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// li r31,0
	ctx.r31.s64 = 0;
	// blt 0x92249f00
	if (ctx.cr0.lt) goto loc_92249F00;
	// mr r31,r11
	ctx.r31.u64 = ctx.r11.u64;
loc_92249F00:
	// subf. r11,r28,r9
	ctx.r11.u64 = ctx.r9.u64 - ctx.r28.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bge 0x92249f0c
	if (!ctx.cr0.lt) goto loc_92249F0C;
	// li r11,0
	ctx.r11.s64 = 0;
loc_92249F0C:
	// slw r30,r10,r30
	ctx.r30.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// slw r31,r10,r31
	ctx.r31.u64 = ctx.r31.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r31.u8 & 0x3F));
	// slw r11,r10,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// mr r9,r24
	ctx.r9.u64 = ctx.r24.u64;
	// mr r8,r26
	ctx.r8.u64 = ctx.r26.u64;
	// mr r7,r27
	ctx.r7.u64 = ctx.r27.u64;
	// stw r30,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r30.u32);
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// stw r31,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r31.u32);
	// addi r5,r1,88
	ctx.r5.s64 = ctx.r1.s64 + 88;
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
	// addi r4,r1,84
	ctx.r4.s64 = ctx.r1.s64 + 84;
	// addi r3,r1,80
	ctx.r3.s64 = ctx.r1.s64 + 80;
	// bl 0x92092428
	ctx.lr = 0x92249F44;
	sub_92092428(ctx, base);
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
loc_92249F48:
	// cmplwi cr6,r22,0
	ctx.cr6.compare<uint32_t>(ctx.r22.u32, 0, ctx.xer);
	// beq cr6,0x92249f54
	if (ctx.cr6.eq) goto loc_92249F54;
	// stw r11,0(r22)
	REX_STORE_U32(ctx.r22.u32 + 0, ctx.r11.u32);
loc_92249F54:
	// cmplwi cr6,r21,0
	ctx.cr6.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// beq cr6,0x92249f64
	if (ctx.cr6.eq) goto loc_92249F64;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// stw r11,0(r21)
	REX_STORE_U32(ctx.r21.u32 + 0, ctx.r11.u32);
loc_92249F64:
	// cmplwi cr6,r20,0
	ctx.cr6.compare<uint32_t>(ctx.r20.u32, 0, ctx.xer);
	// beq cr6,0x92249f70
	if (ctx.cr6.eq) goto loc_92249F70;
	// stw r24,0(r20)
	REX_STORE_U32(ctx.r20.u32 + 0, ctx.r24.u32);
loc_92249F70:
	// cmplwi cr6,r19,0
	ctx.cr6.compare<uint32_t>(ctx.r19.u32, 0, ctx.xer);
	// beq cr6,0x92249f7c
	if (ctx.cr6.eq) goto loc_92249F7C;
	// stw r23,0(r19)
	REX_STORE_U32(ctx.r19.u32 + 0, ctx.r23.u32);
loc_92249F7C:
	// addi r1,r1,224
	ctx.r1.s64 = ctx.r1.s64 + 224;
	// b 0x9205b4a4
	__restgprlr_19(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_92249F88) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b470
	ctx.lr = 0x92249F90;
	__savegprlr_26(ctx, base);
	// stwu r1,-368(r1)
	ea = -368 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// li r29,0
	ctx.r29.s64 = 0;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r26,r4
	ctx.r26.u64 = ctx.r4.u64;
	// mr r31,r5
	ctx.r31.u64 = ctx.r5.u64;
	// mr r27,r30
	ctx.r27.u64 = ctx.r30.u64;
	// stw r29,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r29.u32);
	// bl 0x92098ff0
	ctx.lr = 0x92249FB0;
	sub_92098FF0(ctx, base);
	// stw r3,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r3.u32);
	// cmpwi cr6,r3,1
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 1, ctx.xer);
	// beq cr6,0x9224a0d0
	if (ctx.cr6.eq) goto loc_9224A0D0;
	// cmpwi cr6,r3,2
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 2, ctx.xer);
	// beq cr6,0x9224a0ac
	if (ctx.cr6.eq) goto loc_9224A0AC;
	// cmpwi cr6,r3,3
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 3, ctx.xer);
	// beq cr6,0x9224a070
	if (ctx.cr6.eq) goto loc_9224A070;
	// cmpwi cr6,r3,4
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 4, ctx.xer);
	// beq cr6,0x9224a048
	if (ctx.cr6.eq) goto loc_9224A048;
	// cmpwi cr6,r3,5
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 5, ctx.xer);
	// beq cr6,0x9224a008
	if (ctx.cr6.eq) goto loc_9224A008;
	// cmpwi cr6,r3,8
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 8, ctx.xer);
	// bne cr6,0x9224a2f0
	if (!ctx.cr6.eq) goto loc_9224A2F0;
	// addi r5,r1,176
	ctx.r5.s64 = ctx.r1.s64 + 176;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92093b30
	ctx.lr = 0x92249FF4;
	sub_92093B30(ctx, base);
	// lwz r11,200(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 200);
	// lwz r10,204(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 204);
	// lwz r8,176(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 176);
	// lwz r7,192(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 192);
	// b 0x9224a090
	goto loc_9224A090;
loc_9224A008:
	// addi r5,r1,240
	ctx.r5.s64 = ctx.r1.s64 + 240;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92093b30
	ctx.lr = 0x9224A018;
	sub_92093B30(ctx, base);
	// lwz r11,264(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 264);
	// lwz r10,268(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 268);
	// lwz r9,240(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 240);
	// lwz r8,256(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 256);
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// lwz r11,24(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 24);
	// stw r9,16(r31)
	REX_STORE_U32(ctx.r31.u32 + 16, ctx.r9.u32);
	// rlwinm r11,r11,6,26,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 6) & 0x3F;
	// stw r8,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r8.u32);
	// stw r11,12(r31)
	REX_STORE_U32(ctx.r31.u32 + 12, ctx.r11.u32);
	// b 0x9224a114
	goto loc_9224A114;
loc_9224A048:
	// addi r5,r1,112
	ctx.r5.s64 = ctx.r1.s64 + 112;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92093b38
	ctx.lr = 0x9224A058;
	sub_92093B38(ctx, base);
	// lwz r11,128(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// lwz r10,132(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 132);
	// lwz r9,136(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 136);
	// lwz r8,112(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
	// stw r29,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r29.u32);
	// b 0x9224a098
	goto loc_9224A098;
loc_9224A070:
	// addi r5,r1,208
	ctx.r5.s64 = ctx.r1.s64 + 208;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92093b30
	ctx.lr = 0x9224A080;
	sub_92093B30(ctx, base);
	// lwz r11,232(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 232);
	// lwz r10,236(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 236);
	// lwz r8,208(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 208);
	// lwz r7,224(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 224);
loc_9224A090:
	// li r9,1
	ctx.r9.s64 = 1;
	// stw r7,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r7.u32);
loc_9224A098:
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// stw r9,12(r31)
	REX_STORE_U32(ctx.r31.u32 + 12, ctx.r9.u32);
	// stw r8,16(r31)
	REX_STORE_U32(ctx.r31.u32 + 16, ctx.r8.u32);
	// b 0x9224a114
	goto loc_9224A114;
loc_9224A0AC:
	// addi r4,r1,144
	ctx.r4.s64 = ctx.r1.s64 + 144;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92094090
	ctx.lr = 0x9224A0B8;
	sub_92094090(ctx, base);
	// lwz r11,160(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 160);
	// lwz r10,164(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 164);
	// lwz r9,168(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 168);
	// lwz r8,144(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 144);
	// stw r29,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r29.u32);
	// b 0x9224a0f4
	goto loc_9224A0F4;
loc_9224A0D0:
	// addi r4,r1,272
	ctx.r4.s64 = ctx.r1.s64 + 272;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92094010
	ctx.lr = 0x9224A0DC;
	sub_92094010(ctx, base);
	// lwz r7,288(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 288);
	// lwz r11,296(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 296);
	// li r9,1
	ctx.r9.s64 = 1;
	// lwz r10,300(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 300);
	// lwz r8,272(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 272);
	// stw r7,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r7.u32);
loc_9224A0F4:
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// stw r10,8(r31)
	REX_STORE_U32(ctx.r31.u32 + 8, ctx.r10.u32);
	// stw r9,12(r31)
	REX_STORE_U32(ctx.r31.u32 + 12, ctx.r9.u32);
	// stw r8,16(r31)
	REX_STORE_U32(ctx.r31.u32 + 16, ctx.r8.u32);
	// lwz r11,44(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 44);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq 0x9224a114
	if (ctx.cr0.eq) goto loc_9224A114;
	// mr r27,r11
	ctx.r27.u64 = ctx.r11.u64;
loc_9224A114:
	// lwz r11,16(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 16);
	// addi r5,r1,80
	ctx.r5.s64 = ctx.r1.s64 + 80;
	// addi r4,r1,100
	ctx.r4.s64 = ctx.r1.s64 + 100;
	// clrlwi r3,r11,26
	ctx.r3.u64 = ctx.r11.u32 & 0x3F;
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// addi r11,r11,6232
	ctx.r11.s64 = ctx.r11.s64 + 6232;
	// lbzx r11,r3,r11
	ctx.r11.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r11.u32);
	// stw r29,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r29.u32);
	// stw r11,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r11.u32);
	// bl 0x92092280
	ctx.lr = 0x9224A13C;
	sub_92092280(ctx, base);
	// cmplw cr6,r27,r30
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, ctx.r30.u32, ctx.xer);
	// bne cr6,0x9224a14c
	if (!ctx.cr6.eq) goto loc_9224A14C;
	// mr r29,r26
	ctx.r29.u64 = ctx.r26.u64;
	// b 0x9224a154
	goto loc_9224A154;
loc_9224A14C:
	// lwz r11,32(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// rlwinm r29,r11,30,28,31
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 30) & 0xF;
loc_9224A154:
	// mr r8,r29
	ctx.r8.u64 = ctx.r29.u64;
	// mr r7,r27
	ctx.r7.u64 = ctx.r27.u64;
	// addi r6,r1,88
	ctx.r6.s64 = ctx.r1.s64 + 88;
	// addi r5,r1,96
	ctx.r5.s64 = ctx.r1.s64 + 96;
	// addi r4,r1,84
	ctx.r4.s64 = ctx.r1.s64 + 84;
	// addi r3,r1,92
	ctx.r3.s64 = ctx.r1.s64 + 92;
	// bl 0x92249d30
	ctx.lr = 0x9224A170;
	sub_92249D30(ctx, base);
	// cmplwi cr6,r29,0
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 0, ctx.xer);
	// lwz r29,80(r1)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// bne cr6,0x9224a1ec
	if (!ctx.cr6.eq) goto loc_9224A1EC;
	// lwz r11,36(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 36);
	// rlwinm r10,r11,0,21,22
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x600;
	// cmplwi cr6,r10,512
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 512, ctx.xer);
	// bne cr6,0x9224a1ec
	if (!ctx.cr6.eq) goto loc_9224A1EC;
	// lwz r10,16(r27)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r27.u32 + 16);
	// rlwinm. r10,r10,0,0,0
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0x80000000;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne 0x9224a1ec
	if (!ctx.cr0.eq) goto loc_9224A1EC;
	// lwz r10,20(r27)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r27.u32 + 20);
	// rlwinm. r10,r10,0,21,21
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0x400;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne 0x9224a1ec
	if (!ctx.cr0.eq) goto loc_9224A1EC;
	// rlwinm. r10,r11,0,0,19
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne 0x9224a1ec
	if (!ctx.cr0.eq) goto loc_9224A1EC;
	// rlwinm. r11,r11,0,20,20
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x800;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224a1ec
	if (!ctx.cr0.eq) goto loc_9224A1EC;
	// lwz r11,28(r27)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r27.u32 + 28);
	// rlwinm. r11,r11,0,0,0
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x80000000;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224a1ec
	if (!ctx.cr0.eq) goto loc_9224A1EC;
	// addi r6,r1,84
	ctx.r6.s64 = ctx.r1.s64 + 84;
	// addi r5,r1,80
	ctx.r5.s64 = ctx.r1.s64 + 80;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
	// bl 0x920921b8
	ctx.lr = 0x9224A1D4;
	sub_920921B8(ctx, base);
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// addi r10,r29,-1
	ctx.r10.s64 = ctx.r29.s64 + -1;
	// add r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 + ctx.r29.u64;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// andc r10,r11,r10
	ctx.r10.u64 = ctx.r11.u64 & ~ctx.r10.u64;
	// b 0x9224a1f0
	goto loc_9224A1F0;
loc_9224A1EC:
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
loc_9224A1F0:
	// lwz r11,28(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// lwz r9,92(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// lwz r28,96(r1)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// mullw r11,r9,r11
	ctx.r11.s64 = int64_t(ctx.r9.s32) * int64_t(ctx.r11.s32);
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// cmpwi cr6,r28,0
	ctx.cr6.compare<int32_t>(ctx.r28.s32, 0, ctx.xer);
	// mullw r10,r11,r10
	ctx.r10.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r10.s32);
	// stw r11,20(r31)
	REX_STORE_U32(ctx.r31.u32 + 20, ctx.r11.u32);
	// stw r10,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r10.u32);
	// bne cr6,0x9224a230
	if (!ctx.cr6.eq) goto loc_9224A230;
	// cmplwi cr6,r26,1
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 1, ctx.xer);
	// bgt cr6,0x9224a230
	if (ctx.cr6.gt) goto loc_9224A230;
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
	// bl 0x92098ff0
	ctx.lr = 0x9224A228;
	sub_92098FF0(ctx, base);
	// cmpwi cr6,r3,3
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 3, ctx.xer);
	// beq cr6,0x9224a240
	if (ctx.cr6.eq) goto loc_9224A240;
loc_9224A230:
	// lwz r11,24(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 24);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r11,r11,0,0,19
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// stw r11,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r11.u32);
loc_9224A240:
	// lwz r11,28(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// cmpwi cr6,r28,0
	ctx.cr6.compare<int32_t>(ctx.r28.s32, 0, ctx.xer);
	// rlwinm r11,r11,13,0,18
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 13) & 0xFFFFE000;
	// srawi r11,r11,26
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3FFFFFF) != 0);
	ctx.r11.s64 = ctx.r11.s32 >> 26;
	// stw r11,48(r31)
	REX_STORE_U32(ctx.r31.u32 + 48, ctx.r11.u32);
	// beq cr6,0x9224a264
	if (ctx.cr6.eq) goto loc_9224A264;
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// ori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 | 1;
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
loc_9224A264:
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq cr6,0x9224a27c
	if (ctx.cr6.eq) goto loc_9224A27C;
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// ori r11,r11,2
	ctx.r11.u64 = ctx.r11.u64 | 2;
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
loc_9224A27C:
	// lwz r11,28(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// rlwinm. r11,r11,0,0,0
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x80000000;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224a294
	if (ctx.cr0.eq) goto loc_9224A294;
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// ori r11,r11,8
	ctx.r11.u64 = ctx.r11.u64 | 8;
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
loc_9224A294:
	// lwz r11,100(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// twllei r29,0
	if (ctx.r29.s32 == 0 || ctx.r29.u32 < 0u) ppc_trap(ctx, base, 0);
	// lwz r9,4(r31)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r31.u32 + 4);
	// lwz r10,8(r31)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r31.u32 + 8);
	// mullw r8,r11,r29
	ctx.r8.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r29.s32);
	// lwz r7,28(r31)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// lwz r6,20(r31)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r31.u32 + 20);
	// lwz r5,12(r31)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r31.u32 + 12);
	// stw r5,40(r31)
	REX_STORE_U32(ctx.r31.u32 + 40, ctx.r5.u32);
	// add r9,r11,r9
	ctx.r9.u64 = ctx.r11.u64 + ctx.r9.u64;
	// add r10,r10,r29
	ctx.r10.u64 = ctx.r10.u64 + ctx.r29.u64;
	// addi r9,r9,-1
	ctx.r9.s64 = ctx.r9.s64 + -1;
	// mullw r8,r8,r7
	ctx.r8.s64 = int64_t(ctx.r8.s32) * int64_t(ctx.r7.s32);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// twllei r11,0
	if (ctx.r11.s32 == 0 || ctx.r11.u32 < 0u) ppc_trap(ctx, base, 0);
	// divwu r11,r9,r11
	ctx.r11.u64 = uint32_t(ctx.r11.u32 ? ctx.r9.u32 / ctx.r11.u32 : 0);
	// mullw r7,r6,r29
	ctx.r7.s64 = int64_t(ctx.r6.s32) * int64_t(ctx.r29.s32);
	// stw r11,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r11.u32);
	// stw r7,20(r31)
	REX_STORE_U32(ctx.r31.u32 + 20, ctx.r7.u32);
	// divwu r10,r10,r29
	ctx.r10.u64 = uint32_t(ctx.r29.u32 ? ctx.r10.u32 / ctx.r29.u32 : 0);
	// rlwinm r9,r8,29,3,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 29) & 0x1FFFFFFF;
	// stw r10,36(r31)
	REX_STORE_U32(ctx.r31.u32 + 36, ctx.r10.u32);
	// stw r9,44(r31)
	REX_STORE_U32(ctx.r31.u32 + 44, ctx.r9.u32);
loc_9224A2F0:
	// addi r1,r1,368
	ctx.r1.s64 = ctx.r1.s64 + 368;
	// b 0x9205b4c0
	__restgprlr_26(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224A2F8) {
	REX_FUNC_PROLOGUE();
	// b 0x92249f88
	sub_92249F88(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224A300) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b46c
	ctx.lr = 0x9224A308;
	__savegprlr_25(ctx, base);
	// stwu r1,-176(r1)
	ea = -176 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r31,r4
	ctx.r31.u64 = ctx.r4.u64;
	// addi r6,r1,88
	ctx.r6.s64 = ctx.r1.s64 + 88;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,80
	ctx.r4.s64 = ctx.r1.s64 + 80;
	// lwz r11,28(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// rlwinm r29,r11,1,31,31
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x1;
	// rlwinm r28,r29,1,0,30
	ctx.r28.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 1) & 0xFFFFFFFE;
	// bl 0x920921b8
	ctx.lr = 0x9224A330;
	sub_920921B8(ctx, base);
	// lwz r9,80(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// lwz r8,84(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// subf r10,r28,r9
	ctx.r10.u64 = ctx.r9.u64 - ctx.r28.u64;
	// subf r11,r28,r8
	ctx.r11.u64 = ctx.r8.u64 - ctx.r28.u64;
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// addi r7,r11,-1
	ctx.r7.s64 = ctx.r11.s64 + -1;
	// cntlzw r11,r10
	ctx.r11.u64 = ctx.r10.u32 == 0 ? 32 : __builtin_clz(ctx.r10.u32);
	// cntlzw r10,r7
	ctx.r10.u64 = ctx.r7.u32 == 0 ? 32 : __builtin_clz(ctx.r7.u32);
	// subf r11,r11,r29
	ctx.r11.u64 = ctx.r29.u64 - ctx.r11.u64;
	// subf r10,r10,r29
	ctx.r10.u64 = ctx.r29.u64 - ctx.r10.u64;
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// addi r10,r10,32
	ctx.r10.s64 = ctx.r10.s64 + 32;
	// cmpw cr6,r11,r10
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r10.s32, ctx.xer);
	// blt cr6,0x9224a36c
	if (ctx.cr6.lt) goto loc_9224A36C;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
loc_9224A36C:
	// addic. r11,r11,-4
	ctx.xer.ca = ctx.r11.u32 > 3;
	ctx.r11.s64 = ctx.r11.s64 + -4;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bgt 0x9224a378
	if (ctx.cr0.gt) goto loc_9224A378;
	// li r11,0
	ctx.r11.s64 = 0;
loc_9224A378:
	// subf r9,r28,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r28.u64;
	// stw r11,56(r31)
	REX_STORE_U32(ctx.r31.u32 + 56, ctx.r11.u32);
	// subf r10,r28,r8
	ctx.r10.u64 = ctx.r8.u64 - ctx.r28.u64;
	// addi r9,r9,-1
	ctx.r9.s64 = ctx.r9.s64 + -1;
	// addi r8,r10,-1
	ctx.r8.s64 = ctx.r10.s64 + -1;
	// cntlzw r10,r9
	ctx.r10.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
	// cntlzw r9,r8
	ctx.r9.u64 = ctx.r8.u32 == 0 ? 32 : __builtin_clz(ctx.r8.u32);
	// lwz r8,36(r30)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// subf r10,r10,r29
	ctx.r10.u64 = ctx.r29.u64 - ctx.r10.u64;
	// rlwinm r6,r8,0,21,22
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 0) & 0x600;
	// subf r9,r9,r29
	ctx.r9.u64 = ctx.r29.u64 - ctx.r9.u64;
	// addi r8,r10,32
	ctx.r8.s64 = ctx.r10.s64 + 32;
	// addi r7,r9,32
	ctx.r7.s64 = ctx.r9.s64 + 32;
	// cmplwi cr6,r6,1024
	ctx.cr6.compare<uint32_t>(ctx.r6.u32, 1024, ctx.xer);
	// bne cr6,0x9224a3d0
	if (!ctx.cr6.eq) goto loc_9224A3D0;
	// lwz r10,88(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// subf r10,r28,r10
	ctx.r10.u64 = ctx.r10.u64 - ctx.r28.u64;
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// cntlzw r10,r10
	ctx.r10.u64 = ctx.r10.u32 == 0 ? 32 : __builtin_clz(ctx.r10.u32);
	// subf r10,r10,r29
	ctx.r10.u64 = ctx.r29.u64 - ctx.r10.u64;
	// addi r10,r10,32
	ctx.r10.s64 = ctx.r10.s64 + 32;
	// b 0x9224a3d4
	goto loc_9224A3D4;
loc_9224A3D0:
	// li r10,0
	ctx.r10.s64 = 0;
loc_9224A3D4:
	// subf. r9,r11,r10
	ctx.r9.u64 = ctx.r10.u64 - ctx.r11.u64;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// subf r8,r11,r8
	ctx.r8.u64 = ctx.r8.u64 - ctx.r11.u64;
	// li r10,1
	ctx.r10.s64 = 1;
	// subf r11,r11,r7
	ctx.r11.u64 = ctx.r7.u64 - ctx.r11.u64;
	// addi r27,r31,4
	ctx.r27.s64 = ctx.r31.s64 + 4;
	// addi r26,r31,8
	ctx.r26.s64 = ctx.r31.s64 + 8;
	// slw r8,r10,r8
	ctx.r8.u64 = ctx.r8.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r8.u8 & 0x3F));
	// slw r11,r10,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// stw r8,0(r27)
	REX_STORE_U32(ctx.r27.u32 + 0, ctx.r8.u32);
	// stw r11,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r11.u32);
	// bgt 0x9224a404
	if (ctx.cr0.gt) goto loc_9224A404;
	// li r9,0
	ctx.r9.s64 = 0;
loc_9224A404:
	// slw r10,r10,r9
	ctx.r10.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r9.u8 & 0x3F));
	// addi r29,r31,12
	ctx.r29.s64 = ctx.r31.s64 + 12;
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// addi r11,r11,18888
	ctx.r11.s64 = ctx.r11.s64 + 18888;
	// mr r3,r27
	ctx.r3.u64 = ctx.r27.u64;
	// stw r10,0(r29)
	REX_STORE_U32(ctx.r29.u32 + 0, ctx.r10.u32);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// lwz r10,20(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 20);
	// mr r5,r29
	ctx.r5.u64 = ctx.r29.u64;
	// rlwinm r10,r10,1,25,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0x7E;
	// lbzx r11,r10,r11
	ctx.r11.u64 = REX_LOAD_U8(ctx.r10.u32 + ctx.r11.u32);
	// stw r11,28(r31)
	REX_STORE_U32(ctx.r31.u32 + 28, ctx.r11.u32);
	// lwz r11,16(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 16);
	// lwz r10,36(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 36);
	// lwz r7,20(r30)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r30.u32 + 20);
	// rlwinm r9,r11,1,31,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x1;
	// rlwinm r8,r10,23,30,31
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 23) & 0x3;
	// lwz r6,28(r31)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// clrlwi r7,r7,26
	ctx.r7.u64 = ctx.r7.u32 & 0x3F;
	// bl 0x92092428
	ctx.lr = 0x9224A458;
	sub_92092428(ctx, base);
	// lwz r28,28(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 28);
	// lwz r27,0(r27)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r27.u32 + 0);
	// addi r5,r1,96
	ctx.r5.s64 = ctx.r1.s64 + 96;
	// lwz r25,0(r29)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// addi r4,r1,92
	ctx.r4.s64 = ctx.r1.s64 + 92;
	// mullw r11,r27,r28
	ctx.r11.s64 = int64_t(ctx.r27.s32) * int64_t(ctx.r28.s32);
	// lwz r26,0(r26)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// rlwinm r29,r11,29,3,31
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// mullw r11,r26,r29
	ctx.r11.s64 = int64_t(ctx.r26.s32) * int64_t(ctx.r29.s32);
	// stw r29,20(r31)
	REX_STORE_U32(ctx.r31.u32 + 20, ctx.r29.u32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r11,r11,0,0,19
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// mullw r10,r11,r25
	ctx.r10.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r25.s32);
	// stw r11,24(r31)
	REX_STORE_U32(ctx.r31.u32 + 24, ctx.r11.u32);
	// stw r10,60(r31)
	REX_STORE_U32(ctx.r31.u32 + 60, ctx.r10.u32);
	// lwz r11,20(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 20);
	// clrlwi r3,r11,26
	ctx.r3.u64 = ctx.r11.u32 & 0x3F;
	// bl 0x92092280
	ctx.lr = 0x9224A4A0;
	sub_92092280(ctx, base);
	// lwz r11,96(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// lwz r10,92(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// add r9,r26,r11
	ctx.r9.u64 = ctx.r26.u64 + ctx.r11.u64;
	// stw r25,40(r31)
	REX_STORE_U32(ctx.r31.u32 + 40, ctx.r25.u32);
	// mullw r6,r28,r10
	ctx.r6.s64 = int64_t(ctx.r28.s32) * int64_t(ctx.r10.s32);
	// lwz r7,56(r31)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r31.u32 + 56);
	// addi r9,r9,-1
	ctx.r9.s64 = ctx.r9.s64 + -1;
	// mullw r6,r6,r11
	ctx.r6.s64 = int64_t(ctx.r6.s32) * int64_t(ctx.r11.s32);
	// mullw r5,r29,r11
	ctx.r5.s64 = int64_t(ctx.r29.s32) * int64_t(ctx.r11.s32);
	// stw r5,20(r31)
	REX_STORE_U32(ctx.r31.u32 + 20, ctx.r5.u32);
	// twllei r11,0
	if (ctx.r11.s32 == 0 || ctx.r11.u32 < 0u) ppc_trap(ctx, base, 0);
	// divwu r11,r9,r11
	ctx.r11.u64 = uint32_t(ctx.r11.u32 ? ctx.r9.u32 / ctx.r11.u32 : 0);
	// add r8,r27,r10
	ctx.r8.u64 = ctx.r27.u64 + ctx.r10.u64;
	// twllei r10,0
	if (ctx.r10.s32 == 0 || ctx.r10.u32 < 0u) ppc_trap(ctx, base, 0);
	// addi r8,r8,-1
	ctx.r8.s64 = ctx.r8.s64 + -1;
	// rlwinm r9,r6,29,3,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r6.u32 | (ctx.r6.u64 << 32), 29) & 0x1FFFFFFF;
	// divwu r10,r8,r10
	ctx.r10.u64 = uint32_t(ctx.r10.u32 ? ctx.r8.u32 / ctx.r10.u32 : 0);
	// stw r11,36(r31)
	REX_STORE_U32(ctx.r31.u32 + 36, ctx.r11.u32);
	// li r11,0
	ctx.r11.s64 = 0;
	// stw r9,44(r31)
	REX_STORE_U32(ctx.r31.u32 + 44, ctx.r9.u32);
	// stw r10,32(r31)
	REX_STORE_U32(ctx.r31.u32 + 32, ctx.r10.u32);
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
	// lwz r11,32(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 32);
	// rlwinm r11,r11,26,28,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 26) & 0xF;
	// cmplw cr6,r7,r11
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, ctx.r11.u32, ctx.xer);
	// bgt cr6,0x9224a510
	if (ctx.cr6.gt) goto loc_9224A510;
	// li r11,2
	ctx.r11.s64 = 2;
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
loc_9224A510:
	// lwz r11,28(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// rlwinm. r11,r11,0,0,0
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x80000000;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224a528
	if (ctx.cr0.eq) goto loc_9224A528;
	// lwz r11,52(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 52);
	// ori r11,r11,8
	ctx.r11.u64 = ctx.r11.u64 | 8;
	// stw r11,52(r31)
	REX_STORE_U32(ctx.r31.u32 + 52, ctx.r11.u32);
loc_9224A528:
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92098ff0
	ctx.lr = 0x9224A530;
	sub_92098FF0(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
	// bl 0x92092318
	ctx.lr = 0x9224A540;
	sub_92092318(ctx, base);
	// stw r3,16(r31)
	REX_STORE_U32(ctx.r31.u32 + 16, ctx.r3.u32);
	// lwz r11,28(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 28);
	// rlwinm r11,r11,13,0,18
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 13) & 0xFFFFE000;
	// srawi r11,r11,26
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3FFFFFF) != 0);
	ctx.r11.s64 = ctx.r11.s32 >> 26;
	// stw r11,48(r31)
	REX_STORE_U32(ctx.r31.u32 + 48, ctx.r11.u32);
	// addi r1,r1,176
	ctx.r1.s64 = ctx.r1.s64 + 176;
	// b 0x9205b4bc
	__restgprlr_25(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224A560) {
	REX_FUNC_PROLOGUE();
	// cntlzw r11,r5
	ctx.r11.u64 = ctx.r5.u32 == 0 ? 32 : __builtin_clz(ctx.r5.u32);
	// rlwinm r11,r11,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// xori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 ^ 1;
	// rlwinm r10,r11,1,0,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// subf r9,r10,r3
	ctx.r9.u64 = ctx.r3.u64 - ctx.r10.u64;
	// subf r10,r10,r4
	ctx.r10.u64 = ctx.r4.u64 - ctx.r10.u64;
	// addi r9,r9,-1
	ctx.r9.s64 = ctx.r9.s64 + -1;
	// addi r8,r10,-1
	ctx.r8.s64 = ctx.r10.s64 + -1;
	// cntlzw r10,r9
	ctx.r10.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
	// cntlzw r9,r8
	ctx.r9.u64 = ctx.r8.u32 == 0 ? 32 : __builtin_clz(ctx.r8.u32);
	// subf r10,r10,r11
	ctx.r10.u64 = ctx.r11.u64 - ctx.r10.u64;
	// subf r9,r9,r11
	ctx.r9.u64 = ctx.r11.u64 - ctx.r9.u64;
	// addi r11,r10,32
	ctx.r11.s64 = ctx.r10.s64 + 32;
	// addi r10,r9,32
	ctx.r10.s64 = ctx.r9.s64 + 32;
	// cmpw cr6,r11,r10
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r10.s32, ctx.xer);
	// blt cr6,0x9224a5a4
	if (ctx.cr6.lt) goto loc_9224A5A4;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
loc_9224A5A4:
	// addic. r11,r11,-4
	ctx.xer.ca = ctx.r11.u32 > 3;
	ctx.r11.s64 = ctx.r11.s64 + -4;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bgt 0x9224a5b0
	if (ctx.cr0.gt) goto loc_9224A5B0;
	// li r11,0
	ctx.r11.s64 = 0;
loc_9224A5B0:
	// mr r3,r11
	ctx.r3.u64 = ctx.r11.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224A5B8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b468
	ctx.lr = 0x9224A5C0;
	__savegprlr_24(ctx, base);
	// stwu r1,-192(r1)
	ea = -192 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// cntlzw r11,r9
	ctx.r11.u64 = ctx.r9.u32 == 0 ? 32 : __builtin_clz(ctx.r9.u32);
	// mr r27,r10
	ctx.r27.u64 = ctx.r10.u64;
	// rlwinm r11,r11,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// mr r26,r7
	ctx.r26.u64 = ctx.r7.u64;
	// xori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 ^ 1;
	// mr r24,r6
	ctx.r24.u64 = ctx.r6.u64;
	// rlwinm r10,r11,1,0,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// subf r7,r10,r3
	ctx.r7.u64 = ctx.r3.u64 - ctx.r10.u64;
	// subf r9,r10,r4
	ctx.r9.u64 = ctx.r4.u64 - ctx.r10.u64;
	// addi r7,r7,-1
	ctx.r7.s64 = ctx.r7.s64 + -1;
	// addi r6,r9,-1
	ctx.r6.s64 = ctx.r9.s64 + -1;
	// cntlzw r9,r7
	ctx.r9.u64 = ctx.r7.u32 == 0 ? 32 : __builtin_clz(ctx.r7.u32);
	// cntlzw r7,r6
	ctx.r7.u64 = ctx.r6.u32 == 0 ? 32 : __builtin_clz(ctx.r6.u32);
	// subf r9,r9,r11
	ctx.r9.u64 = ctx.r11.u64 - ctx.r9.u64;
	// subf r7,r7,r11
	ctx.r7.u64 = ctx.r11.u64 - ctx.r7.u64;
	// addi r9,r9,32
	ctx.r9.s64 = ctx.r9.s64 + 32;
	// addi r7,r7,32
	ctx.r7.s64 = ctx.r7.s64 + 32;
	// cmpw cr6,r9,r7
	ctx.cr6.compare<int32_t>(ctx.r9.s32, ctx.r7.s32, ctx.xer);
	// blt cr6,0x9224a614
	if (ctx.cr6.lt) goto loc_9224A614;
	// mr r9,r7
	ctx.r9.u64 = ctx.r7.u64;
loc_9224A614:
	// addic. r25,r9,-4
	ctx.xer.ca = ctx.r9.u32 > 3;
	ctx.r25.s64 = ctx.r9.s64 + -4;
	ctx.cr0.compare<int32_t>(ctx.r25.s32, 0, ctx.xer);
	// li r6,0
	ctx.r6.s64 = 0;
	// bgt 0x9224a624
	if (ctx.cr0.gt) goto loc_9224A624;
	// mr r25,r6
	ctx.r25.u64 = ctx.r6.u64;
loc_9224A624:
	// cmplw cr6,r24,r25
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, ctx.r25.u32, ctx.xer);
	// bge cr6,0x9224a640
	if (!ctx.cr6.lt) goto loc_9224A640;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r6,0(r27)
	REX_STORE_U32(ctx.r27.u32 + 0, ctx.r6.u32);
	// stw r6,4(r27)
	REX_STORE_U32(ctx.r27.u32 + 4, ctx.r6.u32);
	// stw r6,8(r27)
	REX_STORE_U32(ctx.r27.u32 + 8, ctx.r6.u32);
	// b 0x9224a750
	goto loc_9224A750;
loc_9224A640:
	// subf r7,r10,r3
	ctx.r7.u64 = ctx.r3.u64 - ctx.r10.u64;
	// subf r9,r10,r4
	ctx.r9.u64 = ctx.r4.u64 - ctx.r10.u64;
	// addi r7,r7,-1
	ctx.r7.s64 = ctx.r7.s64 + -1;
	// addi r4,r9,-1
	ctx.r4.s64 = ctx.r9.s64 + -1;
	// cntlzw r9,r7
	ctx.r9.u64 = ctx.r7.u32 == 0 ? 32 : __builtin_clz(ctx.r7.u32);
	// cntlzw r7,r4
	ctx.r7.u64 = ctx.r4.u32 == 0 ? 32 : __builtin_clz(ctx.r4.u32);
	// subf r9,r9,r11
	ctx.r9.u64 = ctx.r11.u64 - ctx.r9.u64;
	// subf r7,r7,r11
	ctx.r7.u64 = ctx.r11.u64 - ctx.r7.u64;
	// cmplwi cr6,r5,1
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 1, ctx.xer);
	// addi r9,r9,32
	ctx.r9.s64 = ctx.r9.s64 + 32;
	// addi r7,r7,32
	ctx.r7.s64 = ctx.r7.s64 + 32;
	// ble cr6,0x9224a688
	if (!ctx.cr6.gt) goto loc_9224A688;
	// subf r10,r10,r5
	ctx.r10.u64 = ctx.r5.u64 - ctx.r10.u64;
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// cntlzw r10,r10
	ctx.r10.u64 = ctx.r10.u32 == 0 ? 32 : __builtin_clz(ctx.r10.u32);
	// subf r11,r10,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r10.u64;
	// addi r11,r11,32
	ctx.r11.s64 = ctx.r11.s64 + 32;
	// b 0x9224a68c
	goto loc_9224A68C;
loc_9224A688:
	// mr r11,r6
	ctx.r11.u64 = ctx.r6.u64;
loc_9224A68C:
	// li r10,1
	ctx.r10.s64 = 1;
	// subf r9,r25,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r25.u64;
	// subf r7,r25,r7
	ctx.r7.u64 = ctx.r7.u64 - ctx.r25.u64;
	// subf. r11,r25,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r25.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// slw r29,r10,r9
	ctx.r29.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r9.u8 & 0x3F));
	// slw r28,r10,r7
	ctx.r28.u64 = ctx.r7.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r7.u8 & 0x3F));
	// ble 0x9224a6ac
	if (!ctx.cr0.gt) goto loc_9224A6AC;
	// mr r6,r11
	ctx.r6.u64 = ctx.r11.u64;
loc_9224A6AC:
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// stw r29,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r29.u32);
	// rlwinm r3,r26,1,0,30
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r26.u32 | (ctx.r26.u64 << 32), 1) & 0xFFFFFFFE;
	// stw r28,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r28.u32);
	// addi r11,r11,18888
	ctx.r11.s64 = ctx.r11.s64 + 18888;
	// slw r30,r10,r6
	ctx.r30.u64 = ctx.r6.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r6.u8 & 0x3F));
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// mr r9,r8
	ctx.r9.u64 = ctx.r8.u64;
	// li r8,1
	ctx.r8.s64 = 1;
	// mr r7,r26
	ctx.r7.u64 = ctx.r26.u64;
	// addi r5,r1,104
	ctx.r5.s64 = ctx.r1.s64 + 104;
	// stw r30,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r30.u32);
	// lbzx r31,r3,r11
	ctx.r31.u64 = REX_LOAD_U8(ctx.r3.u32 + ctx.r11.u32);
	// addi r4,r1,100
	ctx.r4.s64 = ctx.r1.s64 + 100;
	// addi r3,r1,96
	ctx.r3.s64 = ctx.r1.s64 + 96;
	// mr r6,r31
	ctx.r6.u64 = ctx.r31.u64;
	// bl 0x92092428
	ctx.lr = 0x9224A6F0;
	sub_92092428(ctx, base);
	// lwz r11,96(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// addi r8,r1,112
	ctx.r8.s64 = ctx.r1.s64 + 112;
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// rlwinm r7,r11,29,3,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// addi r11,r1,116
	ctx.r11.s64 = ctx.r1.s64 + 116;
	// addi r10,r1,108
	ctx.r10.s64 = ctx.r1.s64 + 108;
	// mr r9,r26
	ctx.r9.u64 = ctx.r26.u64;
	// mr r6,r30
	ctx.r6.u64 = ctx.r30.u64;
	// mr r5,r28
	ctx.r5.u64 = ctx.r28.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// subf r3,r25,r24
	ctx.r3.u64 = ctx.r24.u64 - ctx.r25.u64;
	// lwz r11,100(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// mullw r11,r7,r11
	ctx.r11.s64 = int64_t(ctx.r7.s32) * int64_t(ctx.r11.s32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r8,r11,0,0,19
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// bl 0x92092a30
	ctx.lr = 0x9224A738;
	sub_92092A30(ctx, base);
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// lwz r10,112(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
	// lwz r9,116(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 116);
	// stw r11,0(r27)
	REX_STORE_U32(ctx.r27.u32 + 0, ctx.r11.u32);
	// stw r10,4(r27)
	REX_STORE_U32(ctx.r27.u32 + 4, ctx.r10.u32);
	// stw r9,8(r27)
	REX_STORE_U32(ctx.r27.u32 + 8, ctx.r9.u32);
loc_9224A750:
	// addi r1,r1,192
	ctx.r1.s64 = ctx.r1.s64 + 192;
	// b 0x9205b4b8
	__restgprlr_24(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224A758) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// addi r10,r1,80
	ctx.r10.s64 = ctx.r1.s64 + 80;
	// bl 0x9224a5b8
	ctx.lr = 0x9224A76C;
	sub_9224A5B8(ctx, base);
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224A780) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r30,-24(r1)
	REX_STORE_U64(ctx.r1.u32 + -24, ctx.r30.u64);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r4
	ctx.r31.u64 = ctx.r4.u64;
	// mr r30,r5
	ctx.r30.u64 = ctx.r5.u64;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,80
	ctx.r4.s64 = ctx.r1.s64 + 80;
	// bl 0x92092280
	ctx.lr = 0x9224A7A8;
	sub_92092280(ctx, base);
	// cmplwi cr6,r31,0
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 0, ctx.xer);
	// beq cr6,0x9224a7b8
	if (ctx.cr6.eq) goto loc_9224A7B8;
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
loc_9224A7B8:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x9224a7c8
	if (ctx.cr6.eq) goto loc_9224A7C8;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// stw r11,0(r30)
	REX_STORE_U32(ctx.r30.u32 + 0, ctx.r11.u32);
loc_9224A7C8:
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r30,-24(r1)
	ctx.r30.u64 = REX_LOAD_U64(ctx.r1.u32 + -24);
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224A7E0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x9224A7E8;
	__savegprlr_14(ctx, base);
	// stwu r1,-320(r1)
	ea = -320 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r27,r8
	ctx.r27.u64 = ctx.r8.u64;
	// lwz r22,404(r1)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r1.u32 + 404);
	// mr r25,r10
	ctx.r25.u64 = ctx.r10.u64;
	// stw r9,388(r1)
	REX_STORE_U32(ctx.r1.u32 + 388, ctx.r9.u32);
	// mr r18,r3
	ctx.r18.u64 = ctx.r3.u64;
	// mr r21,r7
	ctx.r21.u64 = ctx.r7.u64;
	// cmplwi cr6,r22,0
	ctx.cr6.compare<uint32_t>(ctx.r22.u32, 0, ctx.xer);
	// stw r27,380(r1)
	REX_STORE_U32(ctx.r1.u32 + 380, ctx.r27.u32);
	// li r16,0
	ctx.r16.s64 = 0;
	// stw r25,396(r1)
	REX_STORE_U32(ctx.r1.u32 + 396, ctx.r25.u32);
	// bne cr6,0x9224a834
	if (!ctx.cr6.eq) goto loc_9224A834;
	// stw r16,144(r1)
	REX_STORE_U32(ctx.r1.u32 + 144, ctx.r16.u32);
	// addi r22,r1,144
	ctx.r22.s64 = ctx.r1.s64 + 144;
	// stw r4,152(r1)
	REX_STORE_U32(ctx.r1.u32 + 152, ctx.r4.u32);
	// stw r16,148(r1)
	REX_STORE_U32(ctx.r1.u32 + 148, ctx.r16.u32);
	// stw r5,156(r1)
	REX_STORE_U32(ctx.r1.u32 + 156, ctx.r5.u32);
	// stw r16,160(r1)
	REX_STORE_U32(ctx.r1.u32 + 160, ctx.r16.u32);
	// stw r6,164(r1)
	REX_STORE_U32(ctx.r1.u32 + 164, ctx.r6.u32);
loc_9224A834:
	// lwz r11,8(r22)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r22.u32 + 8);
	// cmplwi cr6,r21,0
	ctx.cr6.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// lwz r10,0(r22)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r22.u32 + 0);
	// lwz r9,12(r22)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r22.u32 + 12);
	// subf r29,r10,r11
	ctx.r29.u64 = ctx.r11.u64 - ctx.r10.u64;
	// lwz r8,20(r22)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r22.u32 + 20);
	// lwz r11,4(r22)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r22.u32 + 4);
	// lwz r10,16(r22)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r22.u32 + 16);
	// subf r11,r11,r9
	ctx.r11.u64 = ctx.r9.u64 - ctx.r11.u64;
	// subf r26,r10,r8
	ctx.r26.u64 = ctx.r8.u64 - ctx.r10.u64;
	// stw r29,116(r1)
	REX_STORE_U32(ctx.r1.u32 + 116, ctx.r29.u32);
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// stw r26,120(r1)
	REX_STORE_U32(ctx.r1.u32 + 120, ctx.r26.u32);
	// bne cr6,0x9224a87c
	if (!ctx.cr6.eq) goto loc_9224A87C;
	// stw r16,128(r1)
	REX_STORE_U32(ctx.r1.u32 + 128, ctx.r16.u32);
	// addi r21,r1,128
	ctx.r21.s64 = ctx.r1.s64 + 128;
	// stw r16,132(r1)
	REX_STORE_U32(ctx.r1.u32 + 132, ctx.r16.u32);
	// stw r16,136(r1)
	REX_STORE_U32(ctx.r1.u32 + 136, ctx.r16.u32);
loc_9224A87C:
	// addi r11,r4,31
	ctx.r11.s64 = ctx.r4.s64 + 31;
	// lwz r31,412(r1)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r1.u32 + 412);
	// addi r10,r5,31
	ctx.r10.s64 = ctx.r5.s64 + 31;
	// rlwinm r11,r11,0,0,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// rlwinm r28,r10,0,0,26
	ctx.r28.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFE0;
	// cmplw cr6,r27,r18
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, ctx.r18.u32, ctx.xer);
	// stw r11,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r11.u32);
	// bne cr6,0x9224a8d8
	if (!ctx.cr6.eq) goto loc_9224A8D8;
	// addi r10,r6,3
	ctx.r10.s64 = ctx.r6.s64 + 3;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// rlwinm r10,r10,0,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFC;
	// mullw r10,r10,r28
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r28.s32);
	// mullw r11,r10,r11
	ctx.r11.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r11.s32);
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r30,r11,0,0,19
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x921efbf8
	ctx.lr = 0x9224A8C4;
	sub_921EFBF8(ctx, base);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r27
	ctx.r4.u64 = ctx.r27.u64;
	// mr r19,r3
	ctx.r19.u64 = ctx.r3.u64;
	// bl 0x9224b160
	ctx.lr = 0x9224A8D4;
	sub_9224B160(ctx, base);
	// b 0x9224a8dc
	goto loc_9224A8DC;
loc_9224A8D8:
	// mr r19,r27
	ctx.r19.u64 = ctx.r27.u64;
loc_9224A8DC:
	// rlwinm r10,r31,30,2,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 30) & 0x3FFFFFFF;
	// lwz r11,0(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// rlwinm r9,r31,28,4,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 28) & 0xFFFFFFF;
	// rlwinm r6,r31,31,1,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 31) & 0x7FFFFFFF;
	// subf r8,r10,r9
	ctx.r8.u64 = ctx.r9.u64 - ctx.r10.u64;
	// li r7,1
	ctx.r7.s64 = 1;
	// addi r8,r8,3
	ctx.r8.s64 = ctx.r8.s64 + 3;
	// srw r9,r6,r10
	ctx.r9.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r6.u32 >> (ctx.r10.u8 & 0x3F));
	// add r23,r9,r10
	ctx.r23.u64 = ctx.r9.u64 + ctx.r10.u64;
	// slw r10,r7,r8
	ctx.r10.u64 = ctx.r8.u8 & 0x20 ? 0 : (ctx.r7.u32 << (ctx.r8.u8 & 0x3F));
	// add r9,r11,r29
	ctx.r9.u64 = ctx.r11.u64 + ctx.r29.u64;
	// add r8,r11,r10
	ctx.r8.u64 = ctx.r11.u64 + ctx.r10.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// addi r30,r23,6
	ctx.r30.s64 = ctx.r23.s64 + 6;
	// stw r10,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r10.u32);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// andc r8,r8,r7
	ctx.r8.u64 = ctx.r8.u64 & ~ctx.r7.u64;
	// andc r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 & ~ctx.r10.u64;
	// subf r14,r11,r8
	ctx.r14.u64 = ctx.r8.u64 - ctx.r11.u64;
	// subf r15,r11,r10
	ctx.r15.u64 = ctx.r10.u64 - ctx.r11.u64;
	// cmplw cr6,r14,r29
	ctx.cr6.compare<uint32_t>(ctx.r14.u32, ctx.r29.u32, ctx.xer);
	// mr r11,r29
	ctx.r11.u64 = ctx.r29.u64;
	// bgt cr6,0x9224a93c
	if (ctx.cr6.gt) goto loc_9224A93C;
	// mr r11,r14
	ctx.r11.u64 = ctx.r14.u64;
loc_9224A93C:
	// slw r11,r11,r23
	ctx.r11.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r23.u8 & 0x3F));
	// lwz r10,16(r22)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r22.u32 + 16);
	// stw r16,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r16.u32);
	// cmplwi cr6,r26,0
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 0, ctx.xer);
	// stw r11,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r11.u32);
	// mullw r11,r10,r25
	ctx.r11.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r25.s32);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// beq cr6,0x9224ac50
	if (ctx.cr6.eq) goto loc_9224AC50;
	// rlwinm r11,r28,28,4,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r28.u32 | (ctx.r28.u64 << 32), 28) & 0xFFFFFFF;
	// stw r11,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r11.u32);
loc_9224A964:
	// lwz r10,92(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// lwz r11,8(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 8);
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// lwz r10,80(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// lwz r10,96(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// rlwinm r17,r11,30,2,31
	ctx.r17.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 30) & 0x3FFFFFFF;
	// clrlwi r11,r11,30
	ctx.r11.u64 = ctx.r11.u32 & 0x3;
	// mullw r10,r10,r17
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r17.s32);
	// stw r17,112(r1)
	REX_STORE_U32(ctx.r1.u32 + 112, ctx.r17.u32);
	// stw r10,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r10.u32);
	// beq cr6,0x9224ac30
	if (ctx.cr6.eq) goto loc_9224AC30;
	// slw r20,r11,r30
	ctx.r20.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r30.u8 & 0x3F));
loc_9224A998:
	// lwz r8,0(r22)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r22.u32 + 0);
	// lwz r9,4(r22)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r22.u32 + 4);
	// lwz r7,388(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 388);
	// add r9,r16,r9
	ctx.r9.u64 = ctx.r16.u64 + ctx.r9.u64;
	// lwz r11,4(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 4);
	// lwz r4,104(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 104);
	// mullw r9,r9,r7
	ctx.r9.s64 = int64_t(ctx.r9.s32) * int64_t(ctx.r7.s32);
	// lwz r7,84(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// lwz r5,100(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// add r11,r16,r11
	ctx.r11.u64 = ctx.r16.u64 + ctx.r11.u64;
	// add r28,r9,r7
	ctx.r28.u64 = ctx.r9.u64 + ctx.r7.u64;
	// rlwinm r7,r11,28,4,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 28) & 0xFFFFFFF;
	// slw r8,r8,r23
	ctx.r8.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r23.u8 & 0x3F));
	// add r4,r7,r4
	ctx.r4.u64 = ctx.r7.u64 + ctx.r4.u64;
	// lwz r7,108(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// rlwinm r27,r11,2,27,28
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0x18;
	// clrlwi r9,r10,29
	ctx.r9.u64 = ctx.r10.u32 & 0x7;
	// rlwinm r7,r7,27,5,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r7.u32 | (ctx.r7.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r6,r11,29,3,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// rlwinm r25,r11,4,27,27
	ctx.r25.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 4) & 0x10;
	// add r8,r8,r28
	ctx.r8.u64 = ctx.r8.u64 + ctx.r28.u64;
	// rlwinm r11,r10,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 27) & 0x7FFFFFF;
	// mullw r26,r4,r7
	ctx.r26.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r7.s32);
	// add r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 + ctx.r27.u64;
	// add r4,r8,r19
	ctx.r4.u64 = ctx.r8.u64 + ctx.r19.u64;
	// add r8,r11,r26
	ctx.r8.u64 = ctx.r11.u64 + ctx.r26.u64;
	// add r6,r6,r17
	ctx.r6.u64 = ctx.r6.u64 + ctx.r17.u64;
	// rlwinm r10,r10,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 29) & 0x1FFFFFFF;
	// clrlwi r29,r6,31
	ctx.r29.u64 = ctx.r6.u32 & 0x1;
	// rlwinm r24,r29,1,0,30
	ctx.r24.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 1) & 0xFFFFFFFE;
	// add r10,r10,r24
	ctx.r10.u64 = ctx.r10.u64 + ctx.r24.u64;
	// rlwinm r10,r10,1,29,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0x6;
	// add r10,r10,r29
	ctx.r10.u64 = ctx.r10.u64 + ctx.r29.u64;
	// slw r11,r9,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,26,6,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 26) & 0x3FFFFFF;
	// slw r9,r8,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r7,r11,0,0,27
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFF0;
	// rlwinm r8,r9,1,3,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0x1FFFFFFE;
	// clrlwi r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	// add r11,r8,r7
	ctx.r11.u64 = ctx.r8.u64 + ctx.r7.u64;
	// rlwinm r7,r10,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0x8;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// rlwinm r8,r10,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFE;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224AA88;
	sub_9205B680(ctx, base);
	// mr r31,r14
	ctx.r31.u64 = ctx.r14.u64;
	// cmpw cr6,r14,r15
	ctx.cr6.compare<int32_t>(ctx.r14.s32, ctx.r15.s32, ctx.xer);
	// bge cr6,0x9224ab58
	if (!ctx.cr6.lt) goto loc_9224AB58;
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// slw r17,r11,r23
	ctx.r17.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r23.u8 & 0x3F));
loc_9224AA9C:
	// lwz r10,0(r22)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r22.u32 + 0);
	// mr r5,r17
	ctx.r5.u64 = ctx.r17.u64;
	// lwz r11,0(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// add r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 + ctx.r27.u64;
	// slw r10,r10,r23
	ctx.r10.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r23.u8 & 0x3F));
	// add r10,r10,r28
	ctx.r10.u64 = ctx.r10.u64 + ctx.r28.u64;
	// add r4,r10,r19
	ctx.r4.u64 = ctx.r10.u64 + ctx.r19.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r26
	ctx.r10.u64 = ctx.r10.u64 + ctx.r26.u64;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 + ctx.r29.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// rlwinm r9,r8,1,3,30
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 1) & 0x1FFFFFFE;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224AB44;
	sub_9205B680(ctx, base);
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// add r31,r31,r11
	ctx.r31.u64 = ctx.r31.u64 + ctx.r11.u64;
	// cmpw cr6,r31,r15
	ctx.cr6.compare<int32_t>(ctx.r31.s32, ctx.r15.s32, ctx.xer);
	// blt cr6,0x9224aa9c
	if (ctx.cr6.lt) goto loc_9224AA9C;
	// lwz r17,112(r1)
	ctx.r17.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
loc_9224AB58:
	// lwz r9,116(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 116);
	// cmplw cr6,r31,r9
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x9224ac10
	if (!ctx.cr6.lt) goto loc_9224AC10;
	// lwz r10,0(r22)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r22.u32 + 0);
	// subf r9,r31,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r31.u64;
	// lwz r11,0(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// slw r5,r9,r23
	ctx.r5.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r23.u8 & 0x3F));
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// slw r10,r10,r23
	ctx.r10.u64 = ctx.r23.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r23.u8 & 0x3F));
	// add r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 + ctx.r27.u64;
	// add r10,r10,r28
	ctx.r10.u64 = ctx.r10.u64 + ctx.r28.u64;
	// add r4,r10,r19
	ctx.r4.u64 = ctx.r10.u64 + ctx.r19.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r26
	ctx.r10.u64 = ctx.r10.u64 + ctx.r26.u64;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 + ctx.r29.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// rlwinm r9,r8,1,3,30
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 1) & 0x1FFFFFFE;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224AC10;
	sub_9205B680(ctx, base);
loc_9224AC10:
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// addi r16,r16,1
	ctx.r16.s64 = ctx.r16.s64 + 1;
	// cmplw cr6,r16,r11
	ctx.cr6.compare<uint32_t>(ctx.r16.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x9224a998
	if (ctx.cr6.lt) goto loc_9224A998;
	// lwz r26,120(r1)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r1.u32 + 120);
	// li r16,0
	ctx.r16.s64 = 0;
	// lwz r25,396(r1)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r1.u32 + 396);
	// lwz r27,380(r1)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r1.u32 + 380);
loc_9224AC30:
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// add r10,r10,r25
	ctx.r10.u64 = ctx.r10.u64 + ctx.r25.u64;
	// cmplw cr6,r11,r26
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r26.u32, ctx.xer);
	// stw r11,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
	// stw r10,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r10.u32);
	// blt cr6,0x9224a964
	if (ctx.cr6.lt) goto loc_9224A964;
loc_9224AC50:
	// cmplw cr6,r27,r18
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, ctx.r18.u32, ctx.xer);
	// bne cr6,0x9224ac64
	if (!ctx.cr6.eq) goto loc_9224AC64;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// mr r3,r19
	ctx.r3.u64 = ctx.r19.u64;
	// bl 0x921efc90
	ctx.lr = 0x9224AC64;
	sub_921EFC90(ctx, base);
loc_9224AC64:
	// addi r1,r1,320
	ctx.r1.s64 = ctx.r1.s64 + 320;
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224AC70) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lwz r11,204(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 204);
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// lwz r11,196(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 196);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// bl 0x9224a7e0
	ctx.lr = 0x9224AC90;
	sub_9224A7E0(ctx, base);
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224ACA0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x9224ACA8;
	__savegprlr_14(ctx, base);
	// stwu r1,-320(r1)
	ea = -320 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r24,r5
	ctx.r24.u64 = ctx.r5.u64;
	// lwz r28,404(r1)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r1.u32 + 404);
	// mr r26,r7
	ctx.r26.u64 = ctx.r7.u64;
	// stw r4,348(r1)
	REX_STORE_U32(ctx.r1.u32 + 348, ctx.r4.u32);
	// mr r18,r3
	ctx.r18.u64 = ctx.r3.u64;
	// mr r21,r6
	ctx.r21.u64 = ctx.r6.u64;
	// cmplwi cr6,r28,0
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 0, ctx.xer);
	// stw r24,356(r1)
	REX_STORE_U32(ctx.r1.u32 + 356, ctx.r24.u32);
	// li r16,0
	ctx.r16.s64 = 0;
	// stw r26,372(r1)
	REX_STORE_U32(ctx.r1.u32 + 372, ctx.r26.u32);
	// bne cr6,0x9224acf4
	if (!ctx.cr6.eq) goto loc_9224ACF4;
	// stw r16,144(r1)
	REX_STORE_U32(ctx.r1.u32 + 144, ctx.r16.u32);
	// addi r28,r1,144
	ctx.r28.s64 = ctx.r1.s64 + 144;
	// stw r8,152(r1)
	REX_STORE_U32(ctx.r1.u32 + 152, ctx.r8.u32);
	// stw r16,148(r1)
	REX_STORE_U32(ctx.r1.u32 + 148, ctx.r16.u32);
	// stw r9,156(r1)
	REX_STORE_U32(ctx.r1.u32 + 156, ctx.r9.u32);
	// stw r16,160(r1)
	REX_STORE_U32(ctx.r1.u32 + 160, ctx.r16.u32);
	// stw r10,164(r1)
	REX_STORE_U32(ctx.r1.u32 + 164, ctx.r10.u32);
loc_9224ACF4:
	// lwz r11,8(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 8);
	// cmplwi cr6,r21,0
	ctx.cr6.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// lwz r7,0(r28)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// lwz r6,12(r28)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r28.u32 + 12);
	// subf r29,r7,r11
	ctx.r29.u64 = ctx.r11.u64 - ctx.r7.u64;
	// lwz r5,20(r28)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r28.u32 + 20);
	// lwz r11,4(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 4);
	// lwz r7,16(r28)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r28.u32 + 16);
	// subf r11,r11,r6
	ctx.r11.u64 = ctx.r6.u64 - ctx.r11.u64;
	// subf r25,r7,r5
	ctx.r25.u64 = ctx.r5.u64 - ctx.r7.u64;
	// stw r29,116(r1)
	REX_STORE_U32(ctx.r1.u32 + 116, ctx.r29.u32);
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// stw r25,120(r1)
	REX_STORE_U32(ctx.r1.u32 + 120, ctx.r25.u32);
	// bne cr6,0x9224ad3c
	if (!ctx.cr6.eq) goto loc_9224AD3C;
	// stw r16,128(r1)
	REX_STORE_U32(ctx.r1.u32 + 128, ctx.r16.u32);
	// addi r21,r1,128
	ctx.r21.s64 = ctx.r1.s64 + 128;
	// stw r16,132(r1)
	REX_STORE_U32(ctx.r1.u32 + 132, ctx.r16.u32);
	// stw r16,136(r1)
	REX_STORE_U32(ctx.r1.u32 + 136, ctx.r16.u32);
loc_9224AD3C:
	// addi r11,r8,31
	ctx.r11.s64 = ctx.r8.s64 + 31;
	// lwz r31,412(r1)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r1.u32 + 412);
	// addi r9,r9,31
	ctx.r9.s64 = ctx.r9.s64 + 31;
	// rlwinm r11,r11,0,0,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// rlwinm r27,r9,0,0,26
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 0) & 0xFFFFFFE0;
	// cmplw cr6,r26,r18
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r18.u32, ctx.xer);
	// stw r11,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r11.u32);
	// bne cr6,0x9224ad98
	if (!ctx.cr6.eq) goto loc_9224AD98;
	// addi r10,r10,3
	ctx.r10.s64 = ctx.r10.s64 + 3;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// rlwinm r10,r10,0,0,29
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFC;
	// mullw r10,r10,r27
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r27.s32);
	// mullw r11,r10,r11
	ctx.r11.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r11.s32);
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r30,r11,0,0,19
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x921efbf8
	ctx.lr = 0x9224AD84;
	sub_921EFBF8(ctx, base);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r19,r3
	ctx.r19.u64 = ctx.r3.u64;
	// bl 0x9224b160
	ctx.lr = 0x9224AD94;
	sub_9224B160(ctx, base);
	// b 0x9224ad9c
	goto loc_9224AD9C;
loc_9224AD98:
	// mr r19,r26
	ctx.r19.u64 = ctx.r26.u64;
loc_9224AD9C:
	// rlwinm r10,r31,30,2,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 30) & 0x3FFFFFFF;
	// lwz r11,0(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// rlwinm r9,r31,28,4,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 28) & 0xFFFFFFF;
	// rlwinm r6,r31,31,1,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 31) & 0x7FFFFFFF;
	// subf r8,r10,r9
	ctx.r8.u64 = ctx.r9.u64 - ctx.r10.u64;
	// li r7,1
	ctx.r7.s64 = 1;
	// addi r8,r8,3
	ctx.r8.s64 = ctx.r8.s64 + 3;
	// srw r9,r6,r10
	ctx.r9.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r6.u32 >> (ctx.r10.u8 & 0x3F));
	// add r22,r9,r10
	ctx.r22.u64 = ctx.r9.u64 + ctx.r10.u64;
	// slw r10,r7,r8
	ctx.r10.u64 = ctx.r8.u8 & 0x20 ? 0 : (ctx.r7.u32 << (ctx.r8.u8 & 0x3F));
	// add r9,r11,r29
	ctx.r9.u64 = ctx.r11.u64 + ctx.r29.u64;
	// add r8,r11,r10
	ctx.r8.u64 = ctx.r11.u64 + ctx.r10.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// addi r30,r22,6
	ctx.r30.s64 = ctx.r22.s64 + 6;
	// stw r10,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r10.u32);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// andc r8,r8,r7
	ctx.r8.u64 = ctx.r8.u64 & ~ctx.r7.u64;
	// andc r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 & ~ctx.r10.u64;
	// subf r14,r11,r8
	ctx.r14.u64 = ctx.r8.u64 - ctx.r11.u64;
	// subf r15,r11,r10
	ctx.r15.u64 = ctx.r10.u64 - ctx.r11.u64;
	// cmplw cr6,r14,r29
	ctx.cr6.compare<uint32_t>(ctx.r14.u32, ctx.r29.u32, ctx.xer);
	// mr r11,r29
	ctx.r11.u64 = ctx.r29.u64;
	// bgt cr6,0x9224adfc
	if (ctx.cr6.gt) goto loc_9224ADFC;
	// mr r11,r14
	ctx.r11.u64 = ctx.r14.u64;
loc_9224ADFC:
	// slw r11,r11,r22
	ctx.r11.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r22.u8 & 0x3F));
	// lwz r10,8(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 8);
	// stw r16,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r16.u32);
	// cmplwi cr6,r25,0
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 0, ctx.xer);
	// stw r11,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r11.u32);
	// mullw r11,r10,r24
	ctx.r11.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r24.s32);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// beq cr6,0x9224b110
	if (ctx.cr6.eq) goto loc_9224B110;
	// rlwinm r11,r27,28,4,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 28) & 0xFFFFFFF;
	// stw r11,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r11.u32);
loc_9224AE24:
	// lwz r10,92(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// lwz r11,16(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 16);
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// lwz r10,80(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// lwz r10,96(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// rlwinm r17,r11,30,2,31
	ctx.r17.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 30) & 0x3FFFFFFF;
	// clrlwi r11,r11,30
	ctx.r11.u64 = ctx.r11.u32 & 0x3;
	// mullw r10,r10,r17
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r17.s32);
	// stw r17,112(r1)
	REX_STORE_U32(ctx.r1.u32 + 112, ctx.r17.u32);
	// stw r10,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r10.u32);
	// beq cr6,0x9224b0f0
	if (ctx.cr6.eq) goto loc_9224B0F0;
	// slw r20,r11,r30
	ctx.r20.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r30.u8 & 0x3F));
loc_9224AE58:
	// lwz r8,0(r21)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// lwz r9,4(r21)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r21.u32 + 4);
	// lwz r7,348(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 348);
	// add r9,r9,r16
	ctx.r9.u64 = ctx.r9.u64 + ctx.r16.u64;
	// lwz r11,4(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 4);
	// lwz r4,104(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 104);
	// mullw r9,r9,r7
	ctx.r9.s64 = int64_t(ctx.r9.s32) * int64_t(ctx.r7.s32);
	// lwz r7,84(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// lwz r10,0(r28)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// lwz r5,100(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// add r11,r16,r11
	ctx.r11.u64 = ctx.r16.u64 + ctx.r11.u64;
	// add r27,r9,r7
	ctx.r27.u64 = ctx.r9.u64 + ctx.r7.u64;
	// rlwinm r7,r11,28,4,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 28) & 0xFFFFFFF;
	// slw r8,r8,r22
	ctx.r8.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r22.u8 & 0x3F));
	// add r4,r7,r4
	ctx.r4.u64 = ctx.r7.u64 + ctx.r4.u64;
	// lwz r7,108(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// rlwinm r26,r11,2,27,28
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0x18;
	// clrlwi r9,r10,29
	ctx.r9.u64 = ctx.r10.u32 & 0x7;
	// rlwinm r7,r7,27,5,31
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r7.u32 | (ctx.r7.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r6,r11,29,3,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// rlwinm r24,r11,4,27,27
	ctx.r24.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 4) & 0x10;
	// add r8,r8,r27
	ctx.r8.u64 = ctx.r8.u64 + ctx.r27.u64;
	// rlwinm r11,r10,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 27) & 0x7FFFFFF;
	// mullw r25,r4,r7
	ctx.r25.s64 = int64_t(ctx.r4.s32) * int64_t(ctx.r7.s32);
	// add r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 + ctx.r26.u64;
	// add r3,r8,r18
	ctx.r3.u64 = ctx.r8.u64 + ctx.r18.u64;
	// add r8,r11,r25
	ctx.r8.u64 = ctx.r11.u64 + ctx.r25.u64;
	// add r6,r6,r17
	ctx.r6.u64 = ctx.r6.u64 + ctx.r17.u64;
	// rlwinm r10,r10,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 29) & 0x1FFFFFFF;
	// clrlwi r29,r6,31
	ctx.r29.u64 = ctx.r6.u32 & 0x1;
	// rlwinm r23,r29,1,0,30
	ctx.r23.u64 = __builtin_rotateleft64(ctx.r29.u32 | (ctx.r29.u64 << 32), 1) & 0xFFFFFFFE;
	// add r10,r10,r23
	ctx.r10.u64 = ctx.r10.u64 + ctx.r23.u64;
	// rlwinm r10,r10,1,29,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0x6;
	// add r10,r10,r29
	ctx.r10.u64 = ctx.r10.u64 + ctx.r29.u64;
	// slw r11,r9,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,26,6,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 26) & 0x3FFFFFF;
	// slw r9,r8,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r7,r11,0,0,27
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFF0;
	// rlwinm r8,r9,1,3,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0x1FFFFFFE;
	// clrlwi r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	// add r11,r8,r7
	ctx.r11.u64 = ctx.r8.u64 + ctx.r7.u64;
	// rlwinm r7,r10,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0x8;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// rlwinm r8,r10,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFE;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224AF48;
	sub_9205B680(ctx, base);
	// mr r31,r14
	ctx.r31.u64 = ctx.r14.u64;
	// cmpw cr6,r14,r15
	ctx.cr6.compare<int32_t>(ctx.r14.s32, ctx.r15.s32, ctx.xer);
	// bge cr6,0x9224b018
	if (!ctx.cr6.lt) goto loc_9224B018;
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// slw r17,r11,r22
	ctx.r17.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r22.u8 & 0x3F));
loc_9224AF5C:
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// mr r5,r17
	ctx.r5.u64 = ctx.r17.u64;
	// lwz r11,0(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// add r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 + ctx.r26.u64;
	// slw r10,r10,r22
	ctx.r10.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r22.u8 & 0x3F));
	// add r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 + ctx.r27.u64;
	// add r3,r10,r18
	ctx.r3.u64 = ctx.r10.u64 + ctx.r18.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r25
	ctx.r10.u64 = ctx.r10.u64 + ctx.r25.u64;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 + ctx.r29.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// rlwinm r9,r8,1,3,30
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 1) & 0x1FFFFFFE;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224B004;
	sub_9205B680(ctx, base);
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// add r31,r31,r11
	ctx.r31.u64 = ctx.r31.u64 + ctx.r11.u64;
	// cmpw cr6,r31,r15
	ctx.cr6.compare<int32_t>(ctx.r31.s32, ctx.r15.s32, ctx.xer);
	// blt cr6,0x9224af5c
	if (ctx.cr6.lt) goto loc_9224AF5C;
	// lwz r17,112(r1)
	ctx.r17.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
loc_9224B018:
	// lwz r9,116(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 116);
	// cmplw cr6,r31,r9
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x9224b0d0
	if (!ctx.cr6.lt) goto loc_9224B0D0;
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// subf r9,r31,r9
	ctx.r9.u64 = ctx.r9.u64 - ctx.r31.u64;
	// lwz r11,0(r28)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r28.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// slw r5,r9,r22
	ctx.r5.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r22.u8 & 0x3F));
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// slw r10,r10,r22
	ctx.r10.u64 = ctx.r22.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r22.u8 & 0x3F));
	// add r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 + ctx.r26.u64;
	// add r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 + ctx.r27.u64;
	// add r3,r10,r18
	ctx.r3.u64 = ctx.r10.u64 + ctx.r18.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r25
	ctx.r10.u64 = ctx.r10.u64 + ctx.r25.u64;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 + ctx.r29.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// rlwinm r9,r8,1,3,30
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 1) & 0x1FFFFFFE;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r20
	ctx.r11.u64 = ctx.r11.u64 + ctx.r20.u64;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224B0D0;
	sub_9205B680(ctx, base);
loc_9224B0D0:
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// addi r16,r16,1
	ctx.r16.s64 = ctx.r16.s64 + 1;
	// cmplw cr6,r16,r11
	ctx.cr6.compare<uint32_t>(ctx.r16.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x9224ae58
	if (ctx.cr6.lt) goto loc_9224AE58;
	// lwz r25,120(r1)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r1.u32 + 120);
	// li r16,0
	ctx.r16.s64 = 0;
	// lwz r26,372(r1)
	ctx.r26.u64 = REX_LOAD_U32(ctx.r1.u32 + 372);
	// lwz r24,356(r1)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r1.u32 + 356);
loc_9224B0F0:
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// add r10,r10,r24
	ctx.r10.u64 = ctx.r10.u64 + ctx.r24.u64;
	// cmplw cr6,r11,r25
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r25.u32, ctx.xer);
	// stw r11,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
	// stw r10,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r10.u32);
	// blt cr6,0x9224ae24
	if (ctx.cr6.lt) goto loc_9224AE24;
loc_9224B110:
	// cmplw cr6,r26,r18
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, ctx.r18.u32, ctx.xer);
	// bne cr6,0x9224b124
	if (!ctx.cr6.eq) goto loc_9224B124;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// mr r3,r19
	ctx.r3.u64 = ctx.r19.u64;
	// bl 0x921efc90
	ctx.lr = 0x9224B124;
	sub_921EFC90(ctx, base);
loc_9224B124:
	// addi r1,r1,320
	ctx.r1.s64 = ctx.r1.s64 + 320;
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224B130) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lwz r11,204(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 204);
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// lwz r11,196(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 196);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// bl 0x9224aca0
	ctx.lr = 0x9224B150;
	sub_9224ACA0(ctx, base);
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224B160) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b47c
	ctx.lr = 0x9224B168;
	__savegprlr_29(ctx, base);
	// mr r11,r4
	ctx.r11.u64 = ctx.r4.u64;
	// mr r10,r3
	ctx.r10.u64 = ctx.r3.u64;
	// clrlwi. r9,r11,30
	ctx.r9.u64 = ctx.r11.u32 & 0x3;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// b 0x9224b198
	goto loc_9224B198;
loc_9224B178:
	// cmplwi cr6,r5,1
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 1, ctx.xer);
	// blt cr6,0x9224b1a8
	if (ctx.cr6.lt) goto loc_9224B1A8;
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r5,r5,-1
	ctx.r5.s64 = ctx.r5.s64 + -1;
	// stb r9,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r9.u8);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// clrlwi. r8,r11,30
	ctx.r8.u64 = ctx.r11.u32 & 0x3;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
loc_9224B198:
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// bne 0x9224b178
	if (!ctx.cr0.eq) goto loc_9224B178;
loc_9224B1A8:
	// clrlwi. r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224b1e0
	if (ctx.cr0.eq) goto loc_9224B1E0;
loc_9224B1B0:
	// cmplwi cr6,r5,4
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 4, ctx.xer);
	// blt cr6,0x9224b1e0
	if (ctx.cr6.lt) goto loc_9224B1E0;
	// lwz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// addi r5,r5,-4
	ctx.r5.s64 = ctx.r5.s64 + -4;
	// stw r9,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r9.u32);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// clrlwi. r8,r11,29
	ctx.r8.u64 = ctx.r11.u32 & 0x7;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne 0x9224b1b0
	if (!ctx.cr0.eq) goto loc_9224B1B0;
loc_9224B1E0:
	// clrlwi. r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224b25c
	if (ctx.cr0.eq) goto loc_9224B25C;
loc_9224B1E8:
	// cmplwi cr6,r5,8
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 8, ctx.xer);
	// blt cr6,0x9224b25c
	if (ctx.cr6.lt) goto loc_9224B25C;
	// ld r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U64(ctx.r11.u32 + 0);
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// addi r5,r5,-8
	ctx.r5.s64 = ctx.r5.s64 + -8;
	// std r9,0(r10)
	REX_STORE_U64(ctx.r10.u32 + 0, ctx.r9.u64);
	// addi r10,r10,8
	ctx.r10.s64 = ctx.r10.s64 + 8;
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// clrlwi. r8,r11,28
	ctx.r8.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne 0x9224b1e8
	if (!ctx.cr0.eq) goto loc_9224B1E8;
	// b 0x9224b25c
	goto loc_9224B25C;
loc_9224B21C:
	// cmplwi cr6,r5,16
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 16, ctx.xer);
	// blt cr6,0x9224b380
	if (ctx.cr6.lt) goto loc_9224B380;
	// lvx128 v0,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// li r11,16
	ctx.r11.s64 = 16;
	// stvlx v0,0,r10
	ea = ctx.r10.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// lwz r10,-128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// stvrx v0,r10,r11
	ea = ctx.r10.u32 + ctx.r11.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// lwz r11,-128(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// lwz r8,36(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 36);
	// addi r10,r11,16
	ctx.r10.s64 = ctx.r11.s64 + 16;
	// lwz r11,-124(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -124);
	// addi r5,r8,-16
	ctx.r5.s64 = ctx.r8.s64 + -16;
	// addi r11,r11,16
	ctx.r11.s64 = ctx.r11.s64 + 16;
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
loc_9224B25C:
	// addi r9,r10,15
	ctx.r9.s64 = ctx.r10.s64 + 15;
	// clrlwi r9,r9,25
	ctx.r9.u64 = ctx.r9.u32 & 0x7F;
	// cmplwi cr6,r9,16
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 16, ctx.xer);
	// bge cr6,0x9224b21c
	if (!ctx.cr6.lt) goto loc_9224B21C;
	// b 0x9224b380
	goto loc_9224B380;
loc_9224B270:
	// li r9,15
	ctx.r9.s64 = 15;
	// dcbzl r9,r10
	ea = (ctx.r9.u32 + ctx.r10.u32) & ~127;
	memset((void*)REX_RAW_ADDR(ea), 0, 128);
	// li r9,0
	ctx.r9.s64 = 0;
	// stw r9,-120(r1)
	REX_STORE_U32(ctx.r1.u32 + -120, ctx.r9.u32);
loc_9224B280:
	// li r7,16
	ctx.r7.s64 = 16;
	// lvlx v0,0,r11
	temp.u32 = ctx.r11.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskL[(temp.u32 & 0xF) * 16])));
	// addi r29,r1,-96
	ctx.r29.s64 = ctx.r1.s64 + -96;
	// addi r9,r11,16
	ctx.r9.s64 = ctx.r11.s64 + 16;
	// li r6,16
	ctx.r6.s64 = 16;
	// addi r8,r11,32
	ctx.r8.s64 = ctx.r11.s64 + 32;
	// lvrx v13,r11,r7
	temp.u32 = ctx.r11.u32 + ctx.r7.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, temp.u32 & 0xF ? simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskR[(temp.u32 & 0xF) * 16])) : simde_mm_setzero_si128());
	// li r5,16
	ctx.r5.s64 = 16;
	// vor v0,v0,v13
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_or_si128(simde_mm_load_si128((simde__m128i*)ctx.v0.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8)));
	// addi r11,r11,48
	ctx.r11.s64 = ctx.r11.s64 + 48;
	// li r4,16
	ctx.r4.s64 = 16;
	// li r3,16
	ctx.r3.s64 = 16;
	// li r31,16
	ctx.r31.s64 = 16;
	// stvx v0,r0,r29
	ea = (ctx.r29.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v0.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// li r30,16
	ctx.r30.s64 = 16;
	// lvrx v12,r9,r6
	temp.u32 = ctx.r9.u32 + ctx.r6.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, temp.u32 & 0xF ? simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskR[(temp.u32 & 0xF) * 16])) : simde_mm_setzero_si128());
	// lvlx v13,0,r9
	temp.u32 = ctx.r9.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskL[(temp.u32 & 0xF) * 16])));
	// addi r9,r1,-80
	ctx.r9.s64 = ctx.r1.s64 + -80;
	// vor v13,v13,v12
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_or_si128(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8)));
	// stvx v13,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// addi r9,r1,-64
	ctx.r9.s64 = ctx.r1.s64 + -64;
	// lvrx v12,r8,r5
	temp.u32 = ctx.r8.u32 + ctx.r5.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, temp.u32 & 0xF ? simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskR[(temp.u32 & 0xF) * 16])) : simde_mm_setzero_si128());
	// lvlx v13,0,r8
	temp.u32 = ctx.r8.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskL[(temp.u32 & 0xF) * 16])));
	// vor v13,v13,v12
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_or_si128(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8)));
	// stvx v13,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvlx v13,0,r11
	temp.u32 = ctx.r11.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskL[(temp.u32 & 0xF) * 16])));
	// lvrx v12,r11,r7
	temp.u32 = ctx.r11.u32 + ctx.r7.u32;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, temp.u32 & 0xF ? simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(temp.u32 & ~0xF)), simde_mm_load_si128((simde__m128i*)&VectorMaskR[(temp.u32 & 0xF) * 16])) : simde_mm_setzero_si128());
	// addi r11,r1,-48
	ctx.r11.s64 = ctx.r1.s64 + -48;
	// vor v13,v13,v12
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_or_si128(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8)));
	// stvx v13,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvlx v0,0,r10
	ea = ctx.r10.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// addi r10,r1,-96
	ctx.r10.s64 = ctx.r1.s64 + -96;
	// lwz r11,-128(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// lvx128 v0,r0,r10
	ea = (ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvrx v0,r11,r4
	ea = ctx.r11.u32 + ctx.r4.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// lwz r10,-128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// addi r9,r1,-80
	ctx.r9.s64 = ctx.r1.s64 + -80;
	// addi r11,r10,16
	ctx.r11.s64 = ctx.r10.s64 + 16;
	// lvx128 v0,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvlx v0,0,r11
	ea = ctx.r11.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// stvrx v0,r11,r3
	ea = ctx.r11.u32 + ctx.r3.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// addi r9,r1,-64
	ctx.r9.s64 = ctx.r1.s64 + -64;
	// addi r11,r10,32
	ctx.r11.s64 = ctx.r10.s64 + 32;
	// lvx128 v0,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvlx v0,0,r11
	ea = ctx.r11.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// stvrx v0,r11,r31
	ea = ctx.r11.u32 + ctx.r31.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// addi r9,r1,-48
	ctx.r9.s64 = ctx.r1.s64 + -48;
	// addi r11,r10,48
	ctx.r11.s64 = ctx.r10.s64 + 48;
	// addi r10,r10,64
	ctx.r10.s64 = ctx.r10.s64 + 64;
	// lvx128 v0,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvlx v0,0,r11
	ea = ctx.r11.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// stvrx v0,r11,r30
	ea = ctx.r11.u32 + ctx.r30.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// lwz r11,-120(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -120);
	// lwz r8,36(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 36);
	// addi r9,r11,1
	ctx.r9.s64 = ctx.r11.s64 + 1;
	// lwz r11,-124(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -124);
	// addi r5,r8,-64
	ctx.r5.s64 = ctx.r8.s64 + -64;
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// addi r11,r11,64
	ctx.r11.s64 = ctx.r11.s64 + 64;
	// cmplwi cr6,r9,2
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 2, ctx.xer);
	// stw r9,-120(r1)
	REX_STORE_U32(ctx.r1.u32 + -120, ctx.r9.u32);
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
	// blt cr6,0x9224b280
	if (ctx.cr6.lt) goto loc_9224B280;
loc_9224B380:
	// cmplwi cr6,r5,143
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 143, ctx.xer);
	// bge cr6,0x9224b270
	if (!ctx.cr6.lt) goto loc_9224B270;
	// b 0x9224b3c4
	goto loc_9224B3C4;
loc_9224B38C:
	// lvx128 v0,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// li r11,16
	ctx.r11.s64 = 16;
	// stvlx v0,0,r10
	ea = ctx.r10.u32;
	for (size_t i = 0; i < (16 - (ea & 0xF)); i++)
		REX_STORE_U8(ea + i, ctx.v0.u8[15 - i]);
	// lwz r10,-128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// stvrx v0,r10,r11
	ea = ctx.r10.u32 + ctx.r11.u32;
	for (size_t i = 0; i < (ea & 0xF); i++)
		REX_STORE_U8(ea - i - 1, ctx.v0.u8[i]);
	// lwz r11,36(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 36);
	// lwz r10,-128(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + -128);
	// addi r5,r11,-16
	ctx.r5.s64 = ctx.r11.s64 + -16;
	// lwz r11,-124(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + -124);
	// addi r10,r10,16
	ctx.r10.s64 = ctx.r10.s64 + 16;
	// addi r11,r11,16
	ctx.r11.s64 = ctx.r11.s64 + 16;
	// stw r5,36(r1)
	REX_STORE_U32(ctx.r1.u32 + 36, ctx.r5.u32);
	// stw r10,-128(r1)
	REX_STORE_U32(ctx.r1.u32 + -128, ctx.r10.u32);
	// stw r11,-124(r1)
	REX_STORE_U32(ctx.r1.u32 + -124, ctx.r11.u32);
loc_9224B3C4:
	// cmplwi cr6,r5,16
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 16, ctx.xer);
	// bge cr6,0x9224b38c
	if (!ctx.cr6.lt) goto loc_9224B38C;
	// clrlwi. r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224b3f8
	if (ctx.cr0.eq) goto loc_9224B3F8;
loc_9224B3D4:
	// cmplwi cr6,r5,8
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 8, ctx.xer);
	// blt cr6,0x9224b3f8
	if (ctx.cr6.lt) goto loc_9224B3F8;
	// ld r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U64(ctx.r11.u32 + 0);
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// addi r5,r5,-8
	ctx.r5.s64 = ctx.r5.s64 + -8;
	// std r9,0(r10)
	REX_STORE_U64(ctx.r10.u32 + 0, ctx.r9.u64);
	// addi r10,r10,8
	ctx.r10.s64 = ctx.r10.s64 + 8;
	// clrlwi. r8,r11,28
	ctx.r8.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne 0x9224b3d4
	if (!ctx.cr0.eq) goto loc_9224B3D4;
loc_9224B3F8:
	// clrlwi. r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224b424
	if (ctx.cr0.eq) goto loc_9224B424;
loc_9224B400:
	// cmplwi cr6,r5,4
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 4, ctx.xer);
	// blt cr6,0x9224b424
	if (ctx.cr6.lt) goto loc_9224B424;
	// lwz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// addi r5,r5,-4
	ctx.r5.s64 = ctx.r5.s64 + -4;
	// stw r9,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r9.u32);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// clrlwi. r8,r11,29
	ctx.r8.u64 = ctx.r11.u32 & 0x7;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne 0x9224b400
	if (!ctx.cr0.eq) goto loc_9224B400;
loc_9224B424:
	// clrlwi. r9,r11,30
	ctx.r9.u64 = ctx.r11.u32 & 0x3;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224b450
	if (ctx.cr0.eq) goto loc_9224B450;
loc_9224B42C:
	// cmplwi cr6,r5,1
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 1, ctx.xer);
	// blt cr6,0x9224b450
	if (ctx.cr6.lt) goto loc_9224B450;
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r5,r5,-1
	ctx.r5.s64 = ctx.r5.s64 + -1;
	// stb r9,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r9.u8);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// clrlwi. r8,r11,30
	ctx.r8.u64 = ctx.r11.u32 & 0x3;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// bne 0x9224b42c
	if (!ctx.cr0.eq) goto loc_9224B42C;
loc_9224B450:
	// b 0x9205b4cc
	__restgprlr_29(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224B458) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x9224B460;
	__savegprlr_14(ctx, base);
	// stwu r1,-288(r1)
	ea = -288 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r28,r7
	ctx.r28.u64 = ctx.r7.u64;
	// stw r8,348(r1)
	REX_STORE_U32(ctx.r1.u32 + 348, ctx.r8.u32);
	// mr r21,r9
	ctx.r21.u64 = ctx.r9.u64;
	// mr r18,r3
	ctx.r18.u64 = ctx.r3.u64;
	// mr r30,r4
	ctx.r30.u64 = ctx.r4.u64;
	// mr r29,r5
	ctx.r29.u64 = ctx.r5.u64;
	// mr r20,r6
	ctx.r20.u64 = ctx.r6.u64;
	// stw r28,340(r1)
	REX_STORE_U32(ctx.r1.u32 + 340, ctx.r28.u32);
	// mr r31,r10
	ctx.r31.u64 = ctx.r10.u64;
	// cmplwi cr6,r21,0
	ctx.cr6.compare<uint32_t>(ctx.r21.u32, 0, ctx.xer);
	// bne cr6,0x9224b4ac
	if (!ctx.cr6.eq) goto loc_9224B4AC;
	// mr r7,r29
	ctx.r7.u64 = ctx.r29.u64;
	// mr r6,r30
	ctx.r6.u64 = ctx.r30.u64;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// addi r3,r1,112
	ctx.r3.s64 = ctx.r1.s64 + 112;
	// bl 0x9224c8a8
	ctx.lr = 0x9224B4A8;
	sub_9224C8A8(ctx, base);
	// addi r21,r1,112
	ctx.r21.s64 = ctx.r1.s64 + 112;
loc_9224B4AC:
	// lwz r11,8(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 8);
	// cmplwi cr6,r20,0
	ctx.cr6.compare<uint32_t>(ctx.r20.u32, 0, ctx.xer);
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// li r14,0
	ctx.r14.s64 = 0;
	// lwz r9,12(r21)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r21.u32 + 12);
	// subf r17,r10,r11
	ctx.r17.u64 = ctx.r11.u64 - ctx.r10.u64;
	// lwz r11,4(r21)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r21.u32 + 4);
	// subf r26,r11,r9
	ctx.r26.u64 = ctx.r9.u64 - ctx.r11.u64;
	// stw r17,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r17.u32);
	// stw r26,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r26.u32);
	// bne cr6,0x9224b4e4
	if (!ctx.cr6.eq) goto loc_9224B4E4;
	// stw r14,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r14.u32);
	// addi r20,r1,104
	ctx.r20.s64 = ctx.r1.s64 + 104;
	// stw r14,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r14.u32);
loc_9224B4E4:
	// addi r11,r30,31
	ctx.r11.s64 = ctx.r30.s64 + 31;
	// cmplw cr6,r28,r18
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r18.u32, ctx.xer);
	// rlwinm r27,r11,0,0,26
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// bne cr6,0x9224b52c
	if (!ctx.cr6.eq) goto loc_9224B52C;
	// addi r11,r29,31
	ctx.r11.s64 = ctx.r29.s64 + 31;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// rlwinm r11,r11,0,0,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// mullw r11,r11,r27
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r27.s32);
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r30,r11,0,0,19
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x921efbf8
	ctx.lr = 0x9224B518;
	sub_921EFBF8(ctx, base);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mr r19,r3
	ctx.r19.u64 = ctx.r3.u64;
	// bl 0x9224b160
	ctx.lr = 0x9224B528;
	sub_9224B160(ctx, base);
	// b 0x9224b530
	goto loc_9224B530;
loc_9224B52C:
	// mr r19,r28
	ctx.r19.u64 = ctx.r28.u64;
loc_9224B530:
	// rlwinm r10,r31,30,2,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 30) & 0x3FFFFFFF;
	// lwz r11,0(r20)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// rlwinm r9,r31,28,4,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 28) & 0xFFFFFFF;
	// rlwinm r6,r31,31,1,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 31) & 0x7FFFFFFF;
	// subf r8,r10,r9
	ctx.r8.u64 = ctx.r9.u64 - ctx.r10.u64;
	// li r7,1
	ctx.r7.s64 = 1;
	// addi r8,r8,3
	ctx.r8.s64 = ctx.r8.s64 + 3;
	// srw r9,r6,r10
	ctx.r9.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r6.u32 >> (ctx.r10.u8 & 0x3F));
	// add r29,r9,r10
	ctx.r29.u64 = ctx.r9.u64 + ctx.r10.u64;
	// slw r10,r7,r8
	ctx.r10.u64 = ctx.r8.u8 & 0x20 ? 0 : (ctx.r7.u32 << (ctx.r8.u8 & 0x3F));
	// add r9,r11,r17
	ctx.r9.u64 = ctx.r11.u64 + ctx.r17.u64;
	// add r8,r11,r10
	ctx.r8.u64 = ctx.r11.u64 + ctx.r10.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// addi r30,r29,6
	ctx.r30.s64 = ctx.r29.s64 + 6;
	// stw r10,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r10.u32);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// andc r8,r8,r7
	ctx.r8.u64 = ctx.r8.u64 & ~ctx.r7.u64;
	// andc r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 & ~ctx.r10.u64;
	// subf r15,r11,r8
	ctx.r15.u64 = ctx.r8.u64 - ctx.r11.u64;
	// subf r16,r11,r10
	ctx.r16.u64 = ctx.r10.u64 - ctx.r11.u64;
	// cmplw cr6,r15,r17
	ctx.cr6.compare<uint32_t>(ctx.r15.u32, ctx.r17.u32, ctx.xer);
	// mr r11,r17
	ctx.r11.u64 = ctx.r17.u64;
	// bgt cr6,0x9224b590
	if (ctx.cr6.gt) goto loc_9224B590;
	// mr r11,r15
	ctx.r11.u64 = ctx.r15.u64;
loc_9224B590:
	// slw r11,r11,r29
	ctx.r11.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r29.u8 & 0x3F));
	// cmplwi cr6,r26,0
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 0, ctx.xer);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// beq cr6,0x9224b81c
	if (ctx.cr6.eq) goto loc_9224B81C;
	// rlwinm r11,r27,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r27.u32 | (ctx.r27.u64 << 32), 27) & 0x7FFFFFF;
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
loc_9224B5A8:
	// lwz r9,4(r21)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r21.u32 + 4);
	// lwz r8,0(r21)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// lwz r11,4(r20)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r20.u32 + 4);
	// add r9,r14,r9
	ctx.r9.u64 = ctx.r14.u64 + ctx.r9.u64;
	// lwz r7,348(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 348);
	// add r11,r14,r11
	ctx.r11.u64 = ctx.r14.u64 + ctx.r11.u64;
	// lwz r10,0(r20)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// mullw r28,r9,r7
	ctx.r28.s64 = int64_t(ctx.r9.s32) * int64_t(ctx.r7.s32);
	// lwz r4,88(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// lwz r5,84(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// rlwinm r9,r11,29,31,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1;
	// rlwinm r6,r11,27,5,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r27,r11,2,27,28
	ctx.r27.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0x18;
	// slw r7,r8,r29
	ctx.r7.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r29.u8 & 0x3F));
	// clrlwi r8,r10,29
	ctx.r8.u64 = ctx.r10.u32 & 0x7;
	// rlwinm r24,r11,28,31,31
	ctx.r24.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 28) & 0x1;
	// rlwinm r26,r11,4,27,27
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 4) & 0x10;
	// rlwinm r11,r10,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 27) & 0x7FFFFFF;
	// mullw r25,r6,r4
	ctx.r25.s64 = int64_t(ctx.r6.s32) * int64_t(ctx.r4.s32);
	// add r8,r8,r27
	ctx.r8.u64 = ctx.r8.u64 + ctx.r27.u64;
	// slw r23,r9,r30
	ctx.r23.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r22,r9,1,0,30
	ctx.r22.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0xFFFFFFFE;
	// add r9,r11,r25
	ctx.r9.u64 = ctx.r11.u64 + ctx.r25.u64;
	// add r7,r7,r28
	ctx.r7.u64 = ctx.r7.u64 + ctx.r28.u64;
	// rlwinm r10,r10,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 29) & 0x1FFFFFFF;
	// add r4,r7,r19
	ctx.r4.u64 = ctx.r7.u64 + ctx.r19.u64;
	// add r10,r10,r22
	ctx.r10.u64 = ctx.r10.u64 + ctx.r22.u64;
	// rlwinm r10,r10,1,29,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0x6;
	// add r10,r10,r24
	ctx.r10.u64 = ctx.r10.u64 + ctx.r24.u64;
	// slw r11,r8,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,26,6,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 26) & 0x3FFFFFF;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r7,r11,0,0,27
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r8,r9,3
	ctx.r8.u64 = ctx.r9.u32 & 0x1FFFFFFF;
	// clrlwi r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	// add r11,r8,r7
	ctx.r11.u64 = ctx.r8.u64 + ctx.r7.u64;
	// rlwinm r7,r10,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0x8;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// rlwinm r8,r10,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFE;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// add r11,r11,r26
	ctx.r11.u64 = ctx.r11.u64 + ctx.r26.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224B684;
	sub_9205B680(ctx, base);
	// mr r31,r15
	ctx.r31.u64 = ctx.r15.u64;
	// cmpw cr6,r15,r16
	ctx.cr6.compare<int32_t>(ctx.r15.s32, ctx.r16.s32, ctx.xer);
	// bge cr6,0x9224b754
	if (!ctx.cr6.lt) goto loc_9224B754;
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// slw r17,r11,r29
	ctx.r17.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r29.u8 & 0x3F));
loc_9224B698:
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// mr r5,r17
	ctx.r5.u64 = ctx.r17.u64;
	// lwz r11,0(r20)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// add r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 + ctx.r27.u64;
	// slw r10,r10,r29
	ctx.r10.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r29.u8 & 0x3F));
	// add r10,r10,r28
	ctx.r10.u64 = ctx.r10.u64 + ctx.r28.u64;
	// add r4,r10,r19
	ctx.r4.u64 = ctx.r10.u64 + ctx.r19.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r25
	ctx.r10.u64 = ctx.r10.u64 + ctx.r25.u64;
	// add r11,r11,r22
	ctx.r11.u64 = ctx.r11.u64 + ctx.r22.u64;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// clrlwi r9,r8,3
	ctx.r9.u64 = ctx.r8.u32 & 0x1FFFFFFF;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// add r11,r11,r26
	ctx.r11.u64 = ctx.r11.u64 + ctx.r26.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224B740;
	sub_9205B680(ctx, base);
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// add r31,r31,r11
	ctx.r31.u64 = ctx.r31.u64 + ctx.r11.u64;
	// cmpw cr6,r31,r16
	ctx.cr6.compare<int32_t>(ctx.r31.s32, ctx.r16.s32, ctx.xer);
	// blt cr6,0x9224b698
	if (ctx.cr6.lt) goto loc_9224B698;
	// lwz r17,92(r1)
	ctx.r17.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
loc_9224B754:
	// cmplw cr6,r31,r17
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r17.u32, ctx.xer);
	// bge cr6,0x9224b808
	if (!ctx.cr6.lt) goto loc_9224B808;
	// lwz r10,0(r21)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r21.u32 + 0);
	// subf r9,r31,r17
	ctx.r9.u64 = ctx.r17.u64 - ctx.r31.u64;
	// lwz r11,0(r20)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// slw r5,r9,r29
	ctx.r5.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r29.u8 & 0x3F));
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// slw r10,r10,r29
	ctx.r10.u64 = ctx.r29.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r29.u8 & 0x3F));
	// add r9,r9,r27
	ctx.r9.u64 = ctx.r9.u64 + ctx.r27.u64;
	// add r10,r10,r28
	ctx.r10.u64 = ctx.r10.u64 + ctx.r28.u64;
	// add r4,r10,r19
	ctx.r4.u64 = ctx.r10.u64 + ctx.r19.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r25
	ctx.r10.u64 = ctx.r10.u64 + ctx.r25.u64;
	// add r11,r11,r22
	ctx.r11.u64 = ctx.r11.u64 + ctx.r22.u64;
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r24
	ctx.r11.u64 = ctx.r11.u64 + ctx.r24.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// clrlwi r9,r8,3
	ctx.r9.u64 = ctx.r8.u32 & 0x1FFFFFFF;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// add r11,r11,r26
	ctx.r11.u64 = ctx.r11.u64 + ctx.r26.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r3,r11,r18
	ctx.r3.u64 = ctx.r11.u64 + ctx.r18.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224B808;
	sub_9205B680(ctx, base);
loc_9224B808:
	// lwz r11,96(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// cmplw cr6,r14,r11
	ctx.cr6.compare<uint32_t>(ctx.r14.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x9224b5a8
	if (ctx.cr6.lt) goto loc_9224B5A8;
	// lwz r28,340(r1)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r1.u32 + 340);
loc_9224B81C:
	// cmplw cr6,r28,r18
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, ctx.r18.u32, ctx.xer);
	// bne cr6,0x9224b830
	if (!ctx.cr6.eq) goto loc_9224B830;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// mr r3,r19
	ctx.r3.u64 = ctx.r19.u64;
	// bl 0x921efc90
	ctx.lr = 0x9224B830;
	sub_921EFC90(ctx, base);
loc_9224B830:
	// addi r1,r1,288
	ctx.r1.s64 = ctx.r1.s64 + 288;
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224B838) {
	REX_FUNC_PROLOGUE();
	// b 0x9224b458
	sub_9224B458(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224B840) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x9224B848;
	__savegprlr_14(ctx, base);
	// stwu r1,-288(r1)
	ea = -288 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r27,r6
	ctx.r27.u64 = ctx.r6.u64;
	// stw r4,316(r1)
	REX_STORE_U32(ctx.r1.u32 + 316, ctx.r4.u32);
	// mr r29,r9
	ctx.r29.u64 = ctx.r9.u64;
	// mr r18,r3
	ctx.r18.u64 = ctx.r3.u64;
	// mr r20,r5
	ctx.r20.u64 = ctx.r5.u64;
	// mr r30,r7
	ctx.r30.u64 = ctx.r7.u64;
	// stw r27,332(r1)
	REX_STORE_U32(ctx.r1.u32 + 332, ctx.r27.u32);
	// mr r28,r8
	ctx.r28.u64 = ctx.r8.u64;
	// mr r31,r10
	ctx.r31.u64 = ctx.r10.u64;
	// cmplwi cr6,r29,0
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 0, ctx.xer);
	// bne cr6,0x9224b894
	if (!ctx.cr6.eq) goto loc_9224B894;
	// mr r7,r28
	ctx.r7.u64 = ctx.r28.u64;
	// mr r6,r30
	ctx.r6.u64 = ctx.r30.u64;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// addi r3,r1,112
	ctx.r3.s64 = ctx.r1.s64 + 112;
	// bl 0x9224c8a8
	ctx.lr = 0x9224B890;
	sub_9224C8A8(ctx, base);
	// addi r29,r1,112
	ctx.r29.s64 = ctx.r1.s64 + 112;
loc_9224B894:
	// lwz r11,8(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 8);
	// cmplwi cr6,r20,0
	ctx.cr6.compare<uint32_t>(ctx.r20.u32, 0, ctx.xer);
	// lwz r10,0(r29)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// li r14,0
	ctx.r14.s64 = 0;
	// lwz r9,12(r29)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r29.u32 + 12);
	// subf r17,r10,r11
	ctx.r17.u64 = ctx.r11.u64 - ctx.r10.u64;
	// lwz r11,4(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 4);
	// subf r25,r11,r9
	ctx.r25.u64 = ctx.r9.u64 - ctx.r11.u64;
	// stw r17,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r17.u32);
	// stw r25,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r25.u32);
	// bne cr6,0x9224b8cc
	if (!ctx.cr6.eq) goto loc_9224B8CC;
	// stw r14,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r14.u32);
	// addi r20,r1,104
	ctx.r20.s64 = ctx.r1.s64 + 104;
	// stw r14,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r14.u32);
loc_9224B8CC:
	// addi r11,r30,31
	ctx.r11.s64 = ctx.r30.s64 + 31;
	// cmplw cr6,r27,r18
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, ctx.r18.u32, ctx.xer);
	// rlwinm r26,r11,0,0,26
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// bne cr6,0x9224b914
	if (!ctx.cr6.eq) goto loc_9224B914;
	// addi r11,r28,31
	ctx.r11.s64 = ctx.r28.s64 + 31;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// rlwinm r11,r11,0,0,26
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFE0;
	// mullw r11,r11,r26
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r26.s32);
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// addi r11,r11,4095
	ctx.r11.s64 = ctx.r11.s64 + 4095;
	// rlwinm r30,r11,0,0,19
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFF000;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x921efbf8
	ctx.lr = 0x9224B900;
	sub_921EFBF8(ctx, base);
	// mr r5,r30
	ctx.r5.u64 = ctx.r30.u64;
	// mr r4,r27
	ctx.r4.u64 = ctx.r27.u64;
	// mr r19,r3
	ctx.r19.u64 = ctx.r3.u64;
	// bl 0x9224b160
	ctx.lr = 0x9224B910;
	sub_9224B160(ctx, base);
	// b 0x9224b918
	goto loc_9224B918;
loc_9224B914:
	// mr r19,r27
	ctx.r19.u64 = ctx.r27.u64;
loc_9224B918:
	// rlwinm r10,r31,30,2,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 30) & 0x3FFFFFFF;
	// lwz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// rlwinm r9,r31,28,4,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 28) & 0xFFFFFFF;
	// rlwinm r6,r31,31,1,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 31) & 0x7FFFFFFF;
	// subf r8,r10,r9
	ctx.r8.u64 = ctx.r9.u64 - ctx.r10.u64;
	// li r7,1
	ctx.r7.s64 = 1;
	// addi r8,r8,3
	ctx.r8.s64 = ctx.r8.s64 + 3;
	// srw r9,r6,r10
	ctx.r9.u64 = ctx.r10.u8 & 0x20 ? 0 : (ctx.r6.u32 >> (ctx.r10.u8 & 0x3F));
	// add r28,r9,r10
	ctx.r28.u64 = ctx.r9.u64 + ctx.r10.u64;
	// slw r10,r7,r8
	ctx.r10.u64 = ctx.r8.u8 & 0x20 ? 0 : (ctx.r7.u32 << (ctx.r8.u8 & 0x3F));
	// add r9,r11,r17
	ctx.r9.u64 = ctx.r11.u64 + ctx.r17.u64;
	// add r8,r11,r10
	ctx.r8.u64 = ctx.r11.u64 + ctx.r10.u64;
	// addi r7,r10,-1
	ctx.r7.s64 = ctx.r10.s64 + -1;
	// addi r30,r28,6
	ctx.r30.s64 = ctx.r28.s64 + 6;
	// stw r10,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r10.u32);
	// addi r10,r10,-1
	ctx.r10.s64 = ctx.r10.s64 + -1;
	// andc r8,r8,r7
	ctx.r8.u64 = ctx.r8.u64 & ~ctx.r7.u64;
	// andc r10,r9,r10
	ctx.r10.u64 = ctx.r9.u64 & ~ctx.r10.u64;
	// subf r15,r11,r8
	ctx.r15.u64 = ctx.r8.u64 - ctx.r11.u64;
	// subf r16,r11,r10
	ctx.r16.u64 = ctx.r10.u64 - ctx.r11.u64;
	// cmplw cr6,r15,r17
	ctx.cr6.compare<uint32_t>(ctx.r15.u32, ctx.r17.u32, ctx.xer);
	// mr r11,r17
	ctx.r11.u64 = ctx.r17.u64;
	// bgt cr6,0x9224b978
	if (ctx.cr6.gt) goto loc_9224B978;
	// mr r11,r15
	ctx.r11.u64 = ctx.r15.u64;
loc_9224B978:
	// slw r11,r11,r28
	ctx.r11.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
	// cmplwi cr6,r25,0
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 0, ctx.xer);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// beq cr6,0x9224bc04
	if (ctx.cr6.eq) goto loc_9224BC04;
	// rlwinm r11,r26,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r26.u32 | (ctx.r26.u64 << 32), 27) & 0x7FFFFFF;
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
loc_9224B990:
	// lwz r9,4(r20)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r20.u32 + 4);
	// lwz r8,0(r20)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// lwz r11,4(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 4);
	// add r9,r9,r14
	ctx.r9.u64 = ctx.r9.u64 + ctx.r14.u64;
	// lwz r7,316(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 316);
	// add r11,r14,r11
	ctx.r11.u64 = ctx.r14.u64 + ctx.r11.u64;
	// lwz r10,0(r29)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// mullw r27,r9,r7
	ctx.r27.s64 = int64_t(ctx.r9.s32) * int64_t(ctx.r7.s32);
	// lwz r4,88(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// lwz r5,84(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// rlwinm r9,r11,29,31,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1;
	// rlwinm r6,r11,27,5,31
	ctx.r6.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r26,r11,2,27,28
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0x18;
	// slw r7,r8,r28
	ctx.r7.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r28.u8 & 0x3F));
	// clrlwi r8,r10,29
	ctx.r8.u64 = ctx.r10.u32 & 0x7;
	// rlwinm r23,r11,28,31,31
	ctx.r23.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 28) & 0x1;
	// rlwinm r25,r11,4,27,27
	ctx.r25.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 4) & 0x10;
	// rlwinm r11,r10,27,5,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 27) & 0x7FFFFFF;
	// mullw r24,r6,r4
	ctx.r24.s64 = int64_t(ctx.r6.s32) * int64_t(ctx.r4.s32);
	// add r8,r8,r26
	ctx.r8.u64 = ctx.r8.u64 + ctx.r26.u64;
	// slw r22,r9,r30
	ctx.r22.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r21,r9,1,0,30
	ctx.r21.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 1) & 0xFFFFFFFE;
	// add r9,r11,r24
	ctx.r9.u64 = ctx.r11.u64 + ctx.r24.u64;
	// add r7,r7,r27
	ctx.r7.u64 = ctx.r7.u64 + ctx.r27.u64;
	// rlwinm r10,r10,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 29) & 0x1FFFFFFF;
	// add r3,r7,r18
	ctx.r3.u64 = ctx.r7.u64 + ctx.r18.u64;
	// add r10,r10,r21
	ctx.r10.u64 = ctx.r10.u64 + ctx.r21.u64;
	// rlwinm r10,r10,1,29,30
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 1) & 0x6;
	// add r10,r10,r23
	ctx.r10.u64 = ctx.r10.u64 + ctx.r23.u64;
	// slw r11,r8,r30
	ctx.r11.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r8.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,26,6,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 26) & 0x3FFFFFF;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r7,r11,0,0,27
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r8,r9,3
	ctx.r8.u64 = ctx.r9.u32 & 0x1FFFFFFF;
	// clrlwi r9,r11,28
	ctx.r9.u64 = ctx.r11.u32 & 0xF;
	// add r11,r8,r7
	ctx.r11.u64 = ctx.r8.u64 + ctx.r7.u64;
	// rlwinm r7,r10,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 3) & 0x8;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// rlwinm r8,r10,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFFE;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// add r11,r11,r22
	ctx.r11.u64 = ctx.r11.u64 + ctx.r22.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224BA6C;
	sub_9205B680(ctx, base);
	// mr r31,r15
	ctx.r31.u64 = ctx.r15.u64;
	// cmpw cr6,r15,r16
	ctx.cr6.compare<int32_t>(ctx.r15.s32, ctx.r16.s32, ctx.xer);
	// bge cr6,0x9224bb3c
	if (!ctx.cr6.lt) goto loc_9224BB3C;
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// slw r17,r11,r28
	ctx.r17.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r11.u32 << (ctx.r28.u8 & 0x3F));
loc_9224BA80:
	// lwz r10,0(r20)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// mr r5,r17
	ctx.r5.u64 = ctx.r17.u64;
	// lwz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// add r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 + ctx.r26.u64;
	// slw r10,r10,r28
	ctx.r10.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r28.u8 & 0x3F));
	// add r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 + ctx.r27.u64;
	// add r3,r10,r18
	ctx.r3.u64 = ctx.r10.u64 + ctx.r18.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r24
	ctx.r10.u64 = ctx.r10.u64 + ctx.r24.u64;
	// add r11,r11,r21
	ctx.r11.u64 = ctx.r11.u64 + ctx.r21.u64;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// clrlwi r9,r8,3
	ctx.r9.u64 = ctx.r8.u32 & 0x1FFFFFFF;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r22
	ctx.r11.u64 = ctx.r11.u64 + ctx.r22.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224BB28;
	sub_9205B680(ctx, base);
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// add r31,r31,r11
	ctx.r31.u64 = ctx.r31.u64 + ctx.r11.u64;
	// cmpw cr6,r31,r16
	ctx.cr6.compare<int32_t>(ctx.r31.s32, ctx.r16.s32, ctx.xer);
	// blt cr6,0x9224ba80
	if (ctx.cr6.lt) goto loc_9224BA80;
	// lwz r17,92(r1)
	ctx.r17.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
loc_9224BB3C:
	// cmplw cr6,r31,r17
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r17.u32, ctx.xer);
	// bge cr6,0x9224bbf0
	if (!ctx.cr6.lt) goto loc_9224BBF0;
	// lwz r10,0(r20)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r20.u32 + 0);
	// subf r9,r31,r17
	ctx.r9.u64 = ctx.r17.u64 - ctx.r31.u64;
	// lwz r11,0(r29)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r29.u32 + 0);
	// add r10,r10,r31
	ctx.r10.u64 = ctx.r10.u64 + ctx.r31.u64;
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// slw r5,r9,r28
	ctx.r5.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r28.u8 & 0x3F));
	// clrlwi r9,r11,29
	ctx.r9.u64 = ctx.r11.u32 & 0x7;
	// slw r10,r10,r28
	ctx.r10.u64 = ctx.r28.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r28.u8 & 0x3F));
	// add r9,r9,r26
	ctx.r9.u64 = ctx.r9.u64 + ctx.r26.u64;
	// add r10,r10,r27
	ctx.r10.u64 = ctx.r10.u64 + ctx.r27.u64;
	// add r3,r10,r18
	ctx.r3.u64 = ctx.r10.u64 + ctx.r18.u64;
	// rlwinm r10,r11,27,5,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x7FFFFFF;
	// rlwinm r11,r11,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// add r10,r10,r24
	ctx.r10.u64 = ctx.r10.u64 + ctx.r24.u64;
	// add r11,r11,r21
	ctx.r11.u64 = ctx.r11.u64 + ctx.r21.u64;
	// rlwinm r11,r11,1,29,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0x6;
	// add r11,r11,r23
	ctx.r11.u64 = ctx.r11.u64 + ctx.r23.u64;
	// rlwinm r7,r11,3,28,28
	ctx.r7.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0x8;
	// slw r9,r9,r30
	ctx.r9.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r30.u8 & 0x3F));
	// slw r8,r10,r30
	ctx.r8.u64 = ctx.r30.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r30.u8 & 0x3F));
	// rlwinm r10,r9,26,6,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 26) & 0x3FFFFFF;
	// clrlwi r9,r8,3
	ctx.r9.u64 = ctx.r8.u32 & 0x1FFFFFFF;
	// rlwinm r8,r11,0,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	// rlwinm r11,r10,0,0,27
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF0;
	// clrlwi r10,r10,28
	ctx.r10.u64 = ctx.r10.u32 & 0xF;
	// add r11,r9,r11
	ctx.r11.u64 = ctx.r9.u64 + ctx.r11.u64;
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r11,r11,r22
	ctx.r11.u64 = ctx.r11.u64 + ctx.r22.u64;
	// add r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 + ctx.r25.u64;
	// srawi r6,r11,6
	ctx.xer.ca = (ctx.r11.s32 < 0) & ((ctx.r11.u32 & 0x3F) != 0);
	ctx.r6.s64 = ctx.r11.s32 >> 6;
	// rlwinm r9,r11,0,0,22
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFE00;
	// clrlwi r10,r11,26
	ctx.r10.u64 = ctx.r11.u32 & 0x3F;
	// clrlwi r11,r6,29
	ctx.r11.u64 = ctx.r6.u32 & 0x7;
	// add r11,r7,r11
	ctx.r11.u64 = ctx.r7.u64 + ctx.r11.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r8
	ctx.r11.u64 = ctx.r11.u64 + ctx.r8.u64;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// add r11,r11,r9
	ctx.r11.u64 = ctx.r11.u64 + ctx.r9.u64;
	// rlwinm r11,r11,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 3) & 0xFFFFFFF8;
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// add r4,r11,r19
	ctx.r4.u64 = ctx.r11.u64 + ctx.r19.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224BBF0;
	sub_9205B680(ctx, base);
loc_9224BBF0:
	// lwz r11,96(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// cmplw cr6,r14,r11
	ctx.cr6.compare<uint32_t>(ctx.r14.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x9224b990
	if (ctx.cr6.lt) goto loc_9224B990;
	// lwz r27,332(r1)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r1.u32 + 332);
loc_9224BC04:
	// cmplw cr6,r27,r18
	ctx.cr6.compare<uint32_t>(ctx.r27.u32, ctx.r18.u32, ctx.xer);
	// bne cr6,0x9224bc18
	if (!ctx.cr6.eq) goto loc_9224BC18;
	// lis r4,9351
	ctx.r4.s64 = 612827136;
	// mr r3,r19
	ctx.r3.u64 = ctx.r19.u64;
	// bl 0x921efc90
	ctx.lr = 0x9224BC18;
	sub_921EFC90(ctx, base);
loc_9224BC18:
	// addi r1,r1,288
	ctx.r1.s64 = ctx.r1.s64 + 288;
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224BC20) {
	REX_FUNC_PROLOGUE();
	// b 0x9224b840
	sub_9224B840(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224BC28) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b474
	ctx.lr = 0x9224BC30;
	__savegprlr_27(ctx, base);
	// stwu r1,-144(r1)
	ea = -144 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,4
	ctx.r11.s64 = 262144;
	// ori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 | 1;
	// cmpw cr6,r5,r11
	ctx.cr6.compare<int32_t>(ctx.r5.s32, ctx.r11.s32, ctx.xer);
	// bne cr6,0x9224bc50
	if (!ctx.cr6.eq) goto loc_9224BC50;
	// lwz r11,0(r4)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r4.u32 + 0);
	// stwbrx r11,0,r3
	REX_STORE_U32(ctx.r3.u32, __builtin_bswap32(ctx.r11.u32));
	// b 0x9224bd78
	goto loc_9224BD78;
loc_9224BC50:
	// lis r11,2
	ctx.r11.s64 = 131072;
	// ori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 | 1;
	// cmpw cr6,r5,r11
	ctx.cr6.compare<int32_t>(ctx.r5.s32, ctx.r11.s32, ctx.xer);
	// bne cr6,0x9224bc6c
	if (!ctx.cr6.eq) goto loc_9224BC6C;
	// lhz r11,0(r4)
	ctx.r11.u64 = REX_LOAD_U16(ctx.r4.u32 + 0);
	// sthbrx r11,0,r3
	REX_STORE_U16(ctx.r3.u32, __builtin_bswap16(ctx.r11.u16));
	// b 0x9224bd78
	goto loc_9224BD78;
loc_9224BC6C:
	// lis r11,4
	ctx.r11.s64 = 262144;
	// ori r11,r11,2
	ctx.r11.u64 = ctx.r11.u64 | 2;
	// cmpw cr6,r5,r11
	ctx.cr6.compare<int32_t>(ctx.r5.s32, ctx.r11.s32, ctx.xer);
	// bne cr6,0x9224bc9c
	if (!ctx.cr6.eq) goto loc_9224BC9C;
	// lwbrx r10,0,r4
	ctx.r10.u64 = __builtin_bswap32(REX_LOAD_U32(ctx.r4.u32));
	// li r11,2
	ctx.r11.s64 = 2;
	// stw r10,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r10.u32);
	// lhz r10,80(r1)
	ctx.r10.u64 = REX_LOAD_U16(ctx.r1.u32 + 80);
	// sthbrx r10,0,r3
	REX_STORE_U16(ctx.r3.u32, __builtin_bswap16(ctx.r10.u16));
	// lhz r10,82(r1)
	ctx.r10.u64 = REX_LOAD_U16(ctx.r1.u32 + 82);
	// sthbrx r10,r11,r3
	REX_STORE_U16(ctx.r11.u32 + ctx.r3.u32, __builtin_bswap16(ctx.r10.u16));
	// b 0x9224bd78
	goto loc_9224BD78;
loc_9224BC9C:
	// clrlwi. r31,r5,16
	ctx.r31.u64 = ctx.r5.u32 & 0xFFFF;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// rlwinm r5,r5,16,16,31
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r5.u32 | (ctx.r5.u64 << 32), 16) & 0xFFFF;
	// beq 0x9224bd6c
	if (ctx.cr0.eq) goto loc_9224BD6C;
	// cmplw cr6,r31,r5
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r5.u32, ctx.xer);
	// beq cr6,0x9224bd6c
	if (ctx.cr6.eq) goto loc_9224BD6C;
	// addi r11,r31,-1
	ctx.r11.s64 = ctx.r31.s64 + -1;
	// cmplw cr6,r3,r4
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, ctx.r4.u32, ctx.xer);
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// subfic r11,r11,32
	ctx.xer.ca = ctx.r11.u32 <= 32;
	ctx.r11.u64 = static_cast<uint64_t>(32) - ctx.r11.u64;
	// srw r11,r5,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r5.u32 >> (ctx.r11.u8 & 0x3F));
	// beq cr6,0x9224bd0c
	if (ctx.cr6.eq) goto loc_9224BD0C;
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x9224bd78
	if (ctx.cr6.eq) goto loc_9224BD78;
	// addi r10,r11,-1
	ctx.r10.s64 = ctx.r11.s64 + -1;
	// mr r28,r3
	ctx.r28.u64 = ctx.r3.u64;
	// mullw r10,r10,r31
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r31.s32);
	// neg r27,r31
	ctx.r27.s64 = static_cast<int64_t>(-ctx.r31.u64);
	// add r29,r10,r4
	ctx.r29.u64 = ctx.r10.u64 + ctx.r4.u64;
	// mr r30,r11
	ctx.r30.u64 = ctx.r11.u64;
loc_9224BCE8:
	// mr r5,r31
	ctx.r5.u64 = ctx.r31.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r28
	ctx.r3.u64 = ctx.r28.u64;
	// bl 0x9205b680
	ctx.lr = 0x9224BCF8;
	sub_9205B680(ctx, base);
	// addic. r30,r30,-1
	ctx.xer.ca = ctx.r30.u32 > 0;
	ctx.r30.s64 = ctx.r30.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// add r29,r27,r29
	ctx.r29.u64 = ctx.r27.u64 + ctx.r29.u64;
	// add r28,r28,r31
	ctx.r28.u64 = ctx.r28.u64 + ctx.r31.u64;
	// bne 0x9224bce8
	if (!ctx.cr0.eq) goto loc_9224BCE8;
	// b 0x9224bd78
	goto loc_9224BD78;
loc_9224BD0C:
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// rlwinm. r8,r10,31,1,31
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 31) & 0x7FFFFFFF;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// beq 0x9224bd78
	if (ctx.cr0.eq) goto loc_9224BD78;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// neg r5,r31
	ctx.r5.s64 = static_cast<int64_t>(-ctx.r31.u64);
	// mullw r11,r11,r31
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// add r10,r11,r4
	ctx.r10.u64 = ctx.r11.u64 + ctx.r4.u64;
loc_9224BD28:
	// cmplwi cr6,r31,0
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 0, ctx.xer);
	// beq cr6,0x9224bd58
	if (ctx.cr6.eq) goto loc_9224BD58;
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
	// subf r7,r10,r3
	ctx.r7.u64 = ctx.r3.u64 - ctx.r10.u64;
	// mr r9,r31
	ctx.r9.u64 = ctx.r31.u64;
loc_9224BD3C:
	// lbz r4,0(r11)
	ctx.r4.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addic. r9,r9,-1
	ctx.xer.ca = ctx.r9.u32 > 0;
	ctx.r9.s64 = ctx.r9.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// lbzx r6,r7,r11
	ctx.r6.u64 = REX_LOAD_U8(ctx.r7.u32 + ctx.r11.u32);
	// stbx r4,r7,r11
	REX_STORE_U8(ctx.r7.u32 + ctx.r11.u32, ctx.r4.u8);
	// stb r6,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r6.u8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// bne 0x9224bd3c
	if (!ctx.cr0.eq) goto loc_9224BD3C;
loc_9224BD58:
	// addic. r8,r8,-1
	ctx.xer.ca = ctx.r8.u32 > 0;
	ctx.r8.s64 = ctx.r8.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r8.s32, 0, ctx.xer);
	// add r3,r3,r31
	ctx.r3.u64 = ctx.r3.u64 + ctx.r31.u64;
	// add r10,r10,r5
	ctx.r10.u64 = ctx.r10.u64 + ctx.r5.u64;
	// bne 0x9224bd28
	if (!ctx.cr0.eq) goto loc_9224BD28;
	// b 0x9224bd78
	goto loc_9224BD78;
loc_9224BD6C:
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// beq cr6,0x9224bd78
	if (ctx.cr6.eq) goto loc_9224BD78;
	// bl 0x9205b680
	ctx.lr = 0x9224BD78;
	sub_9205B680(ctx, base);
loc_9224BD78:
	// addi r1,r1,144
	ctx.r1.s64 = ctx.r1.s64 + 144;
	// b 0x9205b4c4
	__restgprlr_27(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224BD80) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b460
	ctx.lr = 0x9224BD88;
	__savegprlr_22(ctx, base);
	// stwu r1,-256(r1)
	ea = -256 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,1
	ctx.r11.s64 = 65536;
	// mr r22,r5
	ctx.r22.u64 = ctx.r5.u64;
	// ori r11,r11,515
	ctx.r11.u64 = ctx.r11.u64 | 515;
	// rlwinm r31,r22,16,16,31
	ctx.r31.u64 = __builtin_rotateleft64(ctx.r22.u32 | (ctx.r22.u64 << 32), 16) & 0xFFFF;
	// li r24,16
	ctx.r24.s64 = 16;
	// mr r23,r6
	ctx.r23.u64 = ctx.r6.u64;
	// mr r29,r3
	ctx.r29.u64 = ctx.r3.u64;
	// stw r22,292(r1)
	REX_STORE_U32(ctx.r1.u32 + 292, ctx.r22.u32);
	// stw r11,112(r1)
	REX_STORE_U32(ctx.r1.u32 + 112, ctx.r11.u32);
	// lis r11,1029
	ctx.r11.s64 = 67436544;
	// mr r28,r4
	ctx.r28.u64 = ctx.r4.u64;
	// ori r11,r11,1543
	ctx.r11.u64 = ctx.r11.u64 | 1543;
	// stw r23,300(r1)
	REX_STORE_U32(ctx.r1.u32 + 300, ctx.r23.u32);
	// mr r26,r7
	ctx.r26.u64 = ctx.r7.u64;
	// addi r30,r1,112
	ctx.r30.s64 = ctx.r1.s64 + 112;
	// stw r11,116(r1)
	REX_STORE_U32(ctx.r1.u32 + 116, ctx.r11.u32);
	// lis r11,2057
	ctx.r11.s64 = 134807552;
	// ori r11,r11,2571
	ctx.r11.u64 = ctx.r11.u64 | 2571;
	// stw r11,120(r1)
	REX_STORE_U32(ctx.r1.u32 + 120, ctx.r11.u32);
	// lis r11,3085
	ctx.r11.s64 = 202178560;
	// ori r11,r11,3599
	ctx.r11.u64 = ctx.r11.u64 | 3599;
	// stw r11,124(r1)
	REX_STORE_U32(ctx.r1.u32 + 124, ctx.r11.u32);
	// addi r11,r31,-1
	ctx.r11.s64 = ctx.r31.s64 + -1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// subfic r11,r11,32
	ctx.xer.ca = ctx.r11.u32 <= 32;
	ctx.r11.u64 = static_cast<uint64_t>(32) - ctx.r11.u64;
	// sraw. r11,r24,r11
	temp.u32 = ctx.r11.u32 & 0x3F;
	if (temp.u32 > 0x1F) temp.u32 = 0x1F;
	ctx.xer.ca = (ctx.r24.s32 < 0) & (((ctx.r24.s32 >> temp.u32) << temp.u32) != ctx.r24.s32);
	ctx.r11.s64 = ctx.r24.s32 >> temp.u32;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224be18
	if (ctx.cr0.eq) goto loc_9224BE18;
	// mr r27,r11
	ctx.r27.u64 = ctx.r11.u64;
loc_9224BDFC:
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224BE0C;
	sub_9224BC28(ctx, base);
	// addic. r27,r27,-1
	ctx.xer.ca = ctx.r27.u32 > 0;
	ctx.r27.s64 = ctx.r27.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r27.s32, 0, ctx.xer);
	// add r30,r31,r30
	ctx.r30.u64 = ctx.r31.u64 + ctx.r30.u64;
	// bne 0x9224bdfc
	if (!ctx.cr0.eq) goto loc_9224BDFC;
loc_9224BE18:
	// addi r11,r31,-1
	ctx.r11.s64 = ctx.r31.s64 + -1;
	// li r10,1
	ctx.r10.s64 = 1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// cmpwi cr6,r23,0
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 0, ctx.xer);
	// subfic r11,r11,32
	ctx.xer.ca = ctx.r11.u32 <= 32;
	ctx.r11.u64 = static_cast<uint64_t>(32) - ctx.r11.u64;
	// slw r27,r10,r11
	ctx.r27.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// stw r27,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r27.u32);
	// bge cr6,0x9224be48
	if (!ctx.cr6.lt) goto loc_9224BE48;
	// li r8,-16
	ctx.r8.s64 = -16;
	// li r30,-128
	ctx.r30.s64 = -128;
	// neg r25,r23
	ctx.r25.s64 = static_cast<int64_t>(-ctx.r23.u64);
	// b 0x9224be58
	goto loc_9224BE58;
loc_9224BE48:
	// mr r8,r24
	ctx.r8.u64 = ctx.r24.u64;
	// li r30,128
	ctx.r30.s64 = 128;
	// li r25,0
	ctx.r25.s64 = 0;
	// li r24,0
	ctx.r24.s64 = 0;
loc_9224BE58:
	// slw r31,r26,r11
	ctx.r31.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r26.u32 << (ctx.r11.u8 & 0x3F));
	// stw r24,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r24.u32);
	// stw r25,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r25.u32);
	// li r10,0
	ctx.r10.s64 = 0;
	// stw r30,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r30.u32);
	// addi r9,r1,128
	ctx.r9.s64 = ctx.r1.s64 + 128;
	// stw r8,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r8.u32);
	// li r11,8
	ctx.r11.s64 = 8;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
loc_9224BE7C:
	// mr r7,r10
	ctx.r7.u64 = ctx.r10.u64;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// add r10,r10,r8
	ctx.r10.u64 = ctx.r10.u64 + ctx.r8.u64;
	// stw r7,0(r9)
	REX_STORE_U32(ctx.r9.u32 + 0, ctx.r7.u32);
	// addi r9,r9,4
	ctx.r9.s64 = ctx.r9.s64 + 4;
	// bne 0x9224be7c
	if (!ctx.cr0.eq) goto loc_9224BE7C;
	// add r11,r25,r29
	ctx.r11.u64 = ctx.r25.u64 + ctx.r29.u64;
	// b 0x9224bec8
	goto loc_9224BEC8;
loc_9224BE9C:
	// cmplwi cr6,r31,0
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 0, ctx.xer);
	// beq cr6,0x9224bed0
	if (ctx.cr6.eq) goto loc_9224BED0;
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// mr r4,r28
	ctx.r4.u64 = ctx.r28.u64;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224BEB4;
	sub_9224BC28(ctx, base);
	// subf r31,r27,r31
	ctx.r31.u64 = ctx.r31.u64 - ctx.r27.u64;
	// add r29,r29,r23
	ctx.r29.u64 = ctx.r29.u64 + ctx.r23.u64;
	// add r28,r28,r23
	ctx.r28.u64 = ctx.r28.u64 + ctx.r23.u64;
	// add r11,r29,r25
	ctx.r11.u64 = ctx.r29.u64 + ctx.r25.u64;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
loc_9224BEC8:
	// clrlwi. r11,r11,28
	ctx.r11.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224be9c
	if (!ctx.cr0.eq) goto loc_9224BE9C;
loc_9224BED0:
	// subf r10,r24,r29
	ctx.r10.u64 = ctx.r29.u64 - ctx.r24.u64;
	// subf r11,r24,r28
	ctx.r11.u64 = ctx.r28.u64 - ctx.r24.u64;
	// add r8,r10,r25
	ctx.r8.u64 = ctx.r10.u64 + ctx.r25.u64;
	// add r7,r11,r25
	ctx.r7.u64 = ctx.r11.u64 + ctx.r25.u64;
	// add r10,r8,r24
	ctx.r10.u64 = ctx.r8.u64 + ctx.r24.u64;
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// stw r7,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r7.u32);
	// clrlwi. r11,r10,25
	ctx.r11.u64 = ctx.r10.u32 & 0x7F;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r11,r1,112
	ctx.r11.s64 = ctx.r1.s64 + 112;
	// lvx128 v0,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// beq 0x9224bf58
	if (ctx.cr0.eq) goto loc_9224BF58;
loc_9224BEFC:
	// cmplwi cr6,r31,16
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 16, ctx.xer);
	// blt cr6,0x9224bf48
	if (ctx.cr6.lt) goto loc_9224BF48;
	// lvx128 v13,r0,r7
	ea = (ctx.r7.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// stvx v13,r0,r8
	ea = (ctx.r8.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// lwz r24,100(r1)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// add r8,r10,r11
	ctx.r8.u64 = ctx.r10.u64 + ctx.r11.u64;
	// lwz r9,88(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// add r10,r8,r24
	ctx.r10.u64 = ctx.r8.u64 + ctx.r24.u64;
	// add r7,r9,r11
	ctx.r7.u64 = ctx.r9.u64 + ctx.r11.u64;
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// stw r7,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r7.u32);
	// clrlwi. r11,r10,25
	ctx.r11.u64 = ctx.r10.u32 & 0x7F;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// lwz r10,80(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// addi r31,r10,-16
	ctx.r31.s64 = ctx.r10.s64 + -16;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// bne 0x9224befc
	if (!ctx.cr0.eq) goto loc_9224BEFC;
loc_9224BF48:
	// lwz r23,300(r1)
	ctx.r23.u64 = REX_LOAD_U32(ctx.r1.u32 + 300);
	// lwz r22,292(r1)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r1.u32 + 292);
	// lwz r30,104(r1)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r1.u32 + 104);
	// lwz r25,96(r1)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
loc_9224BF58:
	// cmplwi cr6,r31,128
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 128, ctx.xer);
	// blt cr6,0x9224c03c
	if (ctx.cr6.lt) goto loc_9224C03C;
	// lwz r9,132(r1)
	ctx.r9.u64 = REX_LOAD_U32(ctx.r1.u32 + 132);
	// rlwinm r26,r30,1,0,30
	ctx.r26.u64 = __builtin_rotateleft64(ctx.r30.u32 | (ctx.r30.u64 << 32), 1) & 0xFFFFFFFE;
	// lwz r6,128(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// lwz r5,136(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 136);
	// add r10,r9,r8
	ctx.r10.u64 = ctx.r9.u64 + ctx.r8.u64;
	// lwz r4,140(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 140);
	// add r11,r9,r7
	ctx.r11.u64 = ctx.r9.u64 + ctx.r7.u64;
	// lwz r3,144(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 144);
	// subf r6,r9,r6
	ctx.r6.u64 = ctx.r6.u64 - ctx.r9.u64;
	// lwz r29,148(r1)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r1.u32 + 148);
	// subf r5,r9,r5
	ctx.r5.u64 = ctx.r5.u64 - ctx.r9.u64;
	// lwz r28,152(r1)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r1.u32 + 152);
	// subf r4,r9,r4
	ctx.r4.u64 = ctx.r4.u64 - ctx.r9.u64;
	// lwz r27,156(r1)
	ctx.r27.u64 = REX_LOAD_U32(ctx.r1.u32 + 156);
	// subf r3,r9,r3
	ctx.r3.u64 = ctx.r3.u64 - ctx.r9.u64;
	// subf r29,r9,r29
	ctx.r29.u64 = ctx.r29.u64 - ctx.r9.u64;
	// subf r28,r9,r28
	ctx.r28.u64 = ctx.r28.u64 - ctx.r9.u64;
	// subf r27,r9,r27
	ctx.r27.u64 = ctx.r27.u64 - ctx.r9.u64;
	// rlwinm r9,r31,25,7,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r31.u32 | (ctx.r31.u64 << 32), 25) & 0x1FFFFFF;
loc_9224BFAC:
	// dcbz r0,r8
	ea = (ctx.r8.u32) & ~31;
	memset((void*)REX_RAW_ADDR(ea), 0, 32);
	// dcbt r26,r7
	// lvx128 v13,r6,r11
	ea = (ctx.r6.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvx128 v12,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v11,r5,r11
	ea = (ctx.r5.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v12,v12,v12,v0
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v10,r4,r11
	ea = (ctx.r4.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v11,v11,v11,v0
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// vperm v10,v10,v10,v0
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// add r8,r8,r30
	ctx.r8.u64 = ctx.r8.u64 + ctx.r30.u64;
	// add r7,r7,r30
	ctx.r7.u64 = ctx.r7.u64 + ctx.r30.u64;
	// addic. r9,r9,-1
	ctx.xer.ca = ctx.r9.u32 > 0;
	ctx.r9.s64 = ctx.r9.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// addi r31,r31,-128
	ctx.r31.s64 = ctx.r31.s64 + -128;
	// stvx128 v13,r6,r10
	ea = (ctx.r6.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v12,r0,r10
	ea = (ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx128 v11,r5,r10
	ea = (ctx.r5.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx128 v10,r4,r10
	ea = (ctx.r4.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvx128 v13,r3,r11
	ea = (ctx.r3.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvx128 v12,r29,r11
	ea = (ctx.r29.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v11,r28,r11
	ea = (ctx.r28.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v12,v12,v12,v0
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v10,r27,r11
	ea = (ctx.r27.u32 + ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v11,v11,v11,v0
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// vperm v10,v10,v10,v0
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// add r11,r11,r30
	ctx.r11.u64 = ctx.r11.u64 + ctx.r30.u64;
	// stvx128 v13,r3,r10
	ea = (ctx.r3.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx128 v12,r29,r10
	ea = (ctx.r29.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx128 v11,r28,r10
	ea = (ctx.r28.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx128 v10,r27,r10
	ea = (ctx.r27.u32 + ctx.r10.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// add r10,r10,r30
	ctx.r10.u64 = ctx.r10.u64 + ctx.r30.u64;
	// bne 0x9224bfac
	if (!ctx.cr0.eq) goto loc_9224BFAC;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// stw r7,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r7.u32);
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
loc_9224C03C:
	// cmplwi cr6,r31,16
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 16, ctx.xer);
	// blt cr6,0x9224c090
	if (ctx.cr6.lt) goto loc_9224C090;
loc_9224C044:
	// lvx128 v13,r0,r7
	ea = (ctx.r7.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// stvx v13,r0,r8
	ea = (ctx.r8.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r31,r11,-16
	ctx.r31.s64 = ctx.r11.s64 + -16;
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// add r8,r10,r11
	ctx.r8.u64 = ctx.r10.u64 + ctx.r11.u64;
	// lwz r10,88(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// cmplwi cr6,r31,16
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 16, ctx.xer);
	// add r7,r10,r11
	ctx.r7.u64 = ctx.r10.u64 + ctx.r11.u64;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// stw r8,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r8.u32);
	// stw r7,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r7.u32);
	// bge cr6,0x9224c044
	if (!ctx.cr6.lt) goto loc_9224C044;
	// lwz r23,300(r1)
	ctx.r23.u64 = REX_LOAD_U32(ctx.r1.u32 + 300);
	// lwz r22,292(r1)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r1.u32 + 292);
	// lwz r25,96(r1)
	ctx.r25.u64 = REX_LOAD_U32(ctx.r1.u32 + 96);
	// lwz r24,100(r1)
	ctx.r24.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
loc_9224C090:
	// subf r10,r25,r8
	ctx.r10.u64 = ctx.r8.u64 - ctx.r25.u64;
	// subf r11,r25,r7
	ctx.r11.u64 = ctx.r7.u64 - ctx.r25.u64;
	// add r30,r10,r24
	ctx.r30.u64 = ctx.r10.u64 + ctx.r24.u64;
	// add r29,r11,r24
	ctx.r29.u64 = ctx.r11.u64 + ctx.r24.u64;
	// cmplwi cr6,r31,0
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 0, ctx.xer);
	// beq cr6,0x9224c0cc
	if (ctx.cr6.eq) goto loc_9224C0CC;
loc_9224C0A8:
	// mr r5,r22
	ctx.r5.u64 = ctx.r22.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224C0B8;
	sub_9224BC28(ctx, base);
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// add r30,r30,r23
	ctx.r30.u64 = ctx.r30.u64 + ctx.r23.u64;
	// subf. r31,r11,r31
	ctx.r31.u64 = ctx.r31.u64 - ctx.r11.u64;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// add r29,r29,r23
	ctx.r29.u64 = ctx.r29.u64 + ctx.r23.u64;
	// bne 0x9224c0a8
	if (!ctx.cr0.eq) goto loc_9224C0A8;
loc_9224C0CC:
	// addi r1,r1,256
	ctx.r1.s64 = ctx.r1.s64 + 256;
	// b 0x9205b4b0
	__restgprlr_22(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224C0D8) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b45c
	ctx.lr = 0x9224C0E0;
	__savegprlr_21(ctx, base);
	// stwu r1,-240(r1)
	ea = -240 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,1
	ctx.r11.s64 = 65536;
	// mr r22,r5
	ctx.r22.u64 = ctx.r5.u64;
	// ori r11,r11,515
	ctx.r11.u64 = ctx.r11.u64 | 515;
	// mr r21,r4
	ctx.r21.u64 = ctx.r4.u64;
	// li r10,16
	ctx.r10.s64 = 16;
	// rlwinm r30,r21,16,16,31
	ctx.r30.u64 = __builtin_rotateleft64(ctx.r21.u32 | (ctx.r21.u64 << 32), 16) & 0xFFFF;
	// stw r22,276(r1)
	REX_STORE_U32(ctx.r1.u32 + 276, ctx.r22.u32);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// stw r11,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r11.u32);
	// lis r11,1029
	ctx.r11.s64 = 67436544;
	// stw r21,268(r1)
	REX_STORE_U32(ctx.r1.u32 + 268, ctx.r21.u32);
	// mr r27,r6
	ctx.r27.u64 = ctx.r6.u64;
	// ori r11,r11,1543
	ctx.r11.u64 = ctx.r11.u64 | 1543;
	// addi r29,r1,96
	ctx.r29.s64 = ctx.r1.s64 + 96;
	// stw r11,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r11.u32);
	// lis r11,2057
	ctx.r11.s64 = 134807552;
	// ori r11,r11,2571
	ctx.r11.u64 = ctx.r11.u64 | 2571;
	// stw r11,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r11.u32);
	// lis r11,3085
	ctx.r11.s64 = 202178560;
	// ori r11,r11,3599
	ctx.r11.u64 = ctx.r11.u64 | 3599;
	// stw r11,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r11.u32);
	// addi r11,r30,-1
	ctx.r11.s64 = ctx.r30.s64 + -1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// subfic r11,r11,32
	ctx.xer.ca = ctx.r11.u32 <= 32;
	ctx.r11.u64 = static_cast<uint64_t>(32) - ctx.r11.u64;
	// sraw. r11,r10,r11
	temp.u32 = ctx.r11.u32 & 0x3F;
	if (temp.u32 > 0x1F) temp.u32 = 0x1F;
	ctx.xer.ca = (ctx.r10.s32 < 0) & (((ctx.r10.s32 >> temp.u32) << temp.u32) != ctx.r10.s32);
	ctx.r11.s64 = ctx.r10.s32 >> temp.u32;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224c16c
	if (ctx.cr0.eq) goto loc_9224C16C;
	// mr r28,r11
	ctx.r28.u64 = ctx.r11.u64;
loc_9224C150:
	// mr r5,r21
	ctx.r5.u64 = ctx.r21.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224C160;
	sub_9224BC28(ctx, base);
	// addic. r28,r28,-1
	ctx.xer.ca = ctx.r28.u32 > 0;
	ctx.r28.s64 = ctx.r28.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r28.s32, 0, ctx.xer);
	// add r29,r30,r29
	ctx.r29.u64 = ctx.r30.u64 + ctx.r29.u64;
	// bne 0x9224c150
	if (!ctx.cr0.eq) goto loc_9224C150;
loc_9224C16C:
	// addi r11,r30,-1
	ctx.r11.s64 = ctx.r30.s64 + -1;
	// li r10,1
	ctx.r10.s64 = 1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// cmpwi cr6,r22,0
	ctx.cr6.compare<int32_t>(ctx.r22.s32, 0, ctx.xer);
	// subfic r11,r11,32
	ctx.xer.ca = ctx.r11.u32 <= 32;
	ctx.r11.u64 = static_cast<uint64_t>(32) - ctx.r11.u64;
	// slw r29,r10,r11
	ctx.r29.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r10.u32 << (ctx.r11.u8 & 0x3F));
	// slw r30,r27,r11
	ctx.r30.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r27.u32 << (ctx.r11.u8 & 0x3F));
	// stw r29,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r29.u32);
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// bge cr6,0x9224c1a8
	if (!ctx.cr6.lt) goto loc_9224C1A8;
	// addi r11,r27,-1
	ctx.r11.s64 = ctx.r27.s64 + -1;
	// mullw r11,r11,r22
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r22.s32);
	// neg r22,r22
	ctx.r22.s64 = static_cast<int64_t>(-ctx.r22.u64);
	// add r31,r11,r31
	ctx.r31.u64 = ctx.r11.u64 + ctx.r31.u64;
	// stw r22,276(r1)
	REX_STORE_U32(ctx.r1.u32 + 276, ctx.r22.u32);
loc_9224C1A8:
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// li r11,0
	ctx.r11.s64 = 0;
	// addi r10,r1,112
	ctx.r10.s64 = ctx.r1.s64 + 112;
loc_9224C1B4:
	// mr r9,r11
	ctx.r9.u64 = ctx.r11.u64;
	// addi r11,r11,16
	ctx.r11.s64 = ctx.r11.s64 + 16;
	// cmpwi cr6,r11,128
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 128, ctx.xer);
	// stw r9,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r9.u32);
	// addi r10,r10,4
	ctx.r10.s64 = ctx.r10.s64 + 4;
	// blt cr6,0x9224c1b4
	if (ctx.cr6.lt) goto loc_9224C1B4;
	// add r11,r31,r22
	ctx.r11.u64 = ctx.r31.u64 + ctx.r22.u64;
	// xor r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 ^ ctx.r31.u64;
	// rlwinm. r11,r11,0,0,24
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFF80;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224c210
	if (ctx.cr0.eq) goto loc_9224C210;
	// li r11,128
	ctx.r11.s64 = 128;
	// dcbt r11,r31
	// b 0x9224c210
	goto loc_9224C210;
loc_9224C1E8:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x9224c218
	if (ctx.cr6.eq) goto loc_9224C218;
	// mr r5,r21
	ctx.r5.u64 = ctx.r21.u64;
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224C200;
	sub_9224BC28(ctx, base);
	// add r31,r31,r22
	ctx.r31.u64 = ctx.r31.u64 + ctx.r22.u64;
	// subf r30,r29,r30
	ctx.r30.u64 = ctx.r30.u64 - ctx.r29.u64;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
loc_9224C210:
	// clrlwi. r11,r31,28
	ctx.r11.u64 = ctx.r31.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c1e8
	if (!ctx.cr0.eq) goto loc_9224C1E8;
loc_9224C218:
	// clrlwi. r11,r31,25
	ctx.r11.u64 = ctx.r31.u32 & 0x7F;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// addi r11,r1,96
	ctx.r11.s64 = ctx.r1.s64 + 96;
	// lvx128 v0,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v0.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// beq 0x9224c264
	if (ctx.cr0.eq) goto loc_9224C264;
loc_9224C228:
	// cmplwi cr6,r30,16
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 16, ctx.xer);
	// blt cr6,0x9224c25c
	if (ctx.cr6.lt) goto loc_9224C25C;
	// lvx128 v13,r0,r31
	ea = (ctx.r31.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// stvx v13,r0,r31
	ea = (ctx.r31.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r31,r11,16
	ctx.r31.s64 = ctx.r11.s64 + 16;
	// addi r30,r10,-16
	ctx.r30.s64 = ctx.r10.s64 + -16;
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// clrlwi. r11,r31,25
	ctx.r11.u64 = ctx.r31.u32 & 0x7F;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c228
	if (!ctx.cr0.eq) goto loc_9224C228;
loc_9224C25C:
	// lwz r22,276(r1)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r1.u32 + 276);
	// lwz r21,268(r1)
	ctx.r21.u64 = REX_LOAD_U32(ctx.r1.u32 + 268);
loc_9224C264:
	// cmplwi cr6,r30,128
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 128, ctx.xer);
	// ble cr6,0x9224c358
	if (!ctx.cr6.gt) goto loc_9224C358;
	// lwz r10,116(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 116);
	// addi r9,r30,-129
	ctx.r9.s64 = ctx.r30.s64 + -129;
	// lwz r8,112(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 112);
	// rlwinm r9,r9,25,7,31
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 25) & 0x1FFFFFF;
	// subf r29,r10,r8
	ctx.r29.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,120(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 120);
	// add r11,r10,r31
	ctx.r11.u64 = ctx.r10.u64 + ctx.r31.u64;
	// subf r28,r10,r8
	ctx.r28.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,124(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 124);
	// subf r27,r10,r8
	ctx.r27.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,128(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// subf r26,r10,r8
	ctx.r26.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,132(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 132);
	// subf r25,r10,r8
	ctx.r25.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,136(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 136);
	// subf r24,r10,r8
	ctx.r24.u64 = ctx.r8.u64 - ctx.r10.u64;
	// lwz r8,140(r1)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r1.u32 + 140);
	// subf r23,r10,r8
	ctx.r23.u64 = ctx.r8.u64 - ctx.r10.u64;
	// addi r10,r9,1
	ctx.r10.s64 = ctx.r9.s64 + 1;
loc_9224C2B8:
	// li r9,128
	ctx.r9.s64 = 128;
	// dcbt r9,r31
	// add r9,r29,r11
	ctx.r9.u64 = ctx.r29.u64 + ctx.r11.u64;
	// lvx128 v13,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// add r8,r28,r11
	ctx.r8.u64 = ctx.r28.u64 + ctx.r11.u64;
	// vperm v10,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// add r7,r27,r11
	ctx.r7.u64 = ctx.r27.u64 + ctx.r11.u64;
	// add r6,r26,r11
	ctx.r6.u64 = ctx.r26.u64 + ctx.r11.u64;
	// add r5,r25,r11
	ctx.r5.u64 = ctx.r25.u64 + ctx.r11.u64;
	// lvx128 v13,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// add r4,r24,r11
	ctx.r4.u64 = ctx.r24.u64 + ctx.r11.u64;
	// lvx128 v12,r0,r8
	ea = (ctx.r8.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v11,r0,r7
	ea = (ctx.r7.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v12,v12,v12,v0
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// vperm v11,v11,v11,v0
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// add r3,r23,r11
	ctx.r3.u64 = ctx.r23.u64 + ctx.r11.u64;
	// addic. r10,r10,-1
	ctx.xer.ca = ctx.r10.u32 > 0;
	ctx.r10.s64 = ctx.r10.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// addi r31,r31,128
	ctx.r31.s64 = ctx.r31.s64 + 128;
	// addi r30,r30,-128
	ctx.r30.s64 = ctx.r30.s64 + -128;
	// stvx v13,r0,r9
	ea = (ctx.r9.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v10,r0,r11
	ea = (ctx.r11.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// addi r11,r11,128
	ctx.r11.s64 = ctx.r11.s64 + 128;
	// stvx v12,r0,r8
	ea = (ctx.r8.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v11,r0,r7
	ea = (ctx.r7.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvx128 v13,r0,r6
	ea = (ctx.r6.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lvx128 v12,r0,r5
	ea = (ctx.r5.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v11,r0,r4
	ea = (ctx.r4.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v12,v12,v12,v0
	simde_mm_store_si128((simde__m128i*)ctx.v12.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// lvx128 v10,r0,r3
	ea = (ctx.r3.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v11,v11,v11,v0
	simde_mm_store_si128((simde__m128i*)ctx.v11.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// vperm v10,v10,v10,v0
	simde_mm_store_si128((simde__m128i*)ctx.v10.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// stvx v13,r0,r6
	ea = (ctx.r6.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v12,r0,r5
	ea = (ctx.r5.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v12.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v11,r0,r4
	ea = (ctx.r4.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v11.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// stvx v10,r0,r3
	ea = (ctx.r3.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v10.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// bne 0x9224c2b8
	if (!ctx.cr0.eq) goto loc_9224C2B8;
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
loc_9224C358:
	// cmplwi cr6,r30,16
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 16, ctx.xer);
	// blt cr6,0x9224c394
	if (ctx.cr6.lt) goto loc_9224C394;
loc_9224C360:
	// lvx128 v13,r0,r31
	ea = (ctx.r31.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)REX_RAW_ADDR(ea)), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// vperm v13,v13,v13,v0
	simde_mm_store_si128((simde__m128i*)ctx.v13.u8, rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)ctx.v0.u8)));
	// stvx v13,r0,r31
	ea = (ctx.r31.u32) & ~0xF;
	simde_mm_store_si128((simde__m128i*)REX_RAW_ADDR(ea), simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*)ctx.v13.u8), simde_mm_load_si128((simde__m128i*)VectorMaskL)));
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r30,r11,-16
	ctx.r30.s64 = ctx.r11.s64 + -16;
	// lwz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// addi r31,r11,16
	ctx.r31.s64 = ctx.r11.s64 + 16;
	// cmplwi cr6,r30,16
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 16, ctx.xer);
	// stw r30,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r30.u32);
	// stw r31,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r31.u32);
	// bge cr6,0x9224c360
	if (!ctx.cr6.lt) goto loc_9224C360;
	// lwz r22,276(r1)
	ctx.r22.u64 = REX_LOAD_U32(ctx.r1.u32 + 276);
	// lwz r21,268(r1)
	ctx.r21.u64 = REX_LOAD_U32(ctx.r1.u32 + 268);
loc_9224C394:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x9224c3bc
	if (ctx.cr6.eq) goto loc_9224C3BC;
loc_9224C39C:
	// mr r5,r21
	ctx.r5.u64 = ctx.r21.u64;
	// mr r4,r31
	ctx.r4.u64 = ctx.r31.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224C3AC;
	sub_9224BC28(ctx, base);
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// add r31,r31,r22
	ctx.r31.u64 = ctx.r31.u64 + ctx.r22.u64;
	// subf. r30,r11,r30
	ctx.r30.u64 = ctx.r30.u64 - ctx.r11.u64;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// bne 0x9224c39c
	if (!ctx.cr0.eq) goto loc_9224C39C;
loc_9224C3BC:
	// addi r1,r1,240
	ctx.r1.s64 = ctx.r1.s64 + 240;
	// b 0x9205b4ac
	__restgprlr_21(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224C3C8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b464
	ctx.lr = 0x9224C3D0;
	__savegprlr_23(ctx, base);
	// stwu r1,-160(r1)
	ea = -160 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r23,r5
	ctx.r23.u64 = ctx.r5.u64;
	// mr r28,r4
	ctx.r28.u64 = ctx.r4.u64;
	// mr r30,r7
	ctx.r30.u64 = ctx.r7.u64;
	// rlwinm r25,r23,16,16,31
	ctx.r25.u64 = __builtin_rotateleft64(ctx.r23.u32 | (ctx.r23.u64 << 32), 16) & 0xFFFF;
	// clrlwi r11,r23,16
	ctx.r11.u64 = ctx.r23.u32 & 0xFFFF;
	// cmpwi cr6,r6,0
	ctx.cr6.compare<int32_t>(ctx.r6.s32, 0, ctx.xer);
	// neg r24,r6
	ctx.r24.s64 = static_cast<int64_t>(-ctx.r6.u64);
	// blt cr6,0x9224c3f8
	if (ctx.cr6.lt) goto loc_9224C3F8;
	// mr r24,r6
	ctx.r24.u64 = ctx.r6.u64;
loc_9224C3F8:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x9224c54c
	if (ctx.cr6.eq) goto loc_9224C54C;
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x9224c410
	if (!ctx.cr6.eq) goto loc_9224C410;
	// cmplw cr6,r3,r28
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, ctx.r28.u32, ctx.xer);
	// beq cr6,0x9224c54c
	if (ctx.cr6.eq) goto loc_9224C54C;
loc_9224C410:
	// subf r11,r28,r3
	ctx.r11.u64 = ctx.r3.u64 - ctx.r28.u64;
	// xor r11,r11,r6
	ctx.r11.u64 = ctx.r11.u64 ^ ctx.r6.u64;
	// rlwinm. r11,r11,0,0,0
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x80000000;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224c430
	if (ctx.cr0.eq) goto loc_9224C430;
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r29,r28
	ctx.r29.u64 = ctx.r28.u64;
	// mr r26,r6
	ctx.r26.u64 = ctx.r6.u64;
	// b 0x9224c444
	goto loc_9224C444;
loc_9224C430:
	// addi r11,r30,-1
	ctx.r11.s64 = ctx.r30.s64 + -1;
	// neg r26,r6
	ctx.r26.s64 = static_cast<int64_t>(-ctx.r6.u64);
	// mullw r11,r11,r6
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r6.s32);
	// add r31,r11,r3
	ctx.r31.u64 = ctx.r11.u64 + ctx.r3.u64;
	// add r29,r11,r28
	ctx.r29.u64 = ctx.r11.u64 + ctx.r28.u64;
loc_9224C444:
	// bl 0x921efbf0
	ctx.lr = 0x9224C448;
	sub_921EFBF0(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224c45c
	if (ctx.cr0.eq) goto loc_9224C45C;
	// rlwinm. r11,r3,0,21,22
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r3.u32 | (ctx.r3.u64 << 32), 0) & 0x600;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// li r27,1
	ctx.r27.s64 = 1;
	// beq 0x9224c460
	if (ctx.cr0.eq) goto loc_9224C460;
loc_9224C45C:
	// li r27,0
	ctx.r27.s64 = 0;
loc_9224C460:
	// mr r3,r28
	ctx.r3.u64 = ctx.r28.u64;
	// bl 0x921efbf0
	ctx.lr = 0x9224C468;
	sub_921EFBF0(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224c47c
	if (ctx.cr0.eq) goto loc_9224C47C;
	// rlwinm. r11,r3,0,21,22
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r3.u32 | (ctx.r3.u64 << 32), 0) & 0x600;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// li r11,1
	ctx.r11.s64 = 1;
	// beq 0x9224c480
	if (ctx.cr0.eq) goto loc_9224C480;
loc_9224C47C:
	// li r11,0
	ctx.r11.s64 = 0;
loc_9224C480:
	// cmpwi cr6,r27,0
	ctx.cr6.compare<int32_t>(ctx.r27.s32, 0, ctx.xer);
	// beq cr6,0x9224c524
	if (ctx.cr6.eq) goto loc_9224C524;
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq cr6,0x9224c524
	if (ctx.cr6.eq) goto loc_9224C524;
	// cmplwi cr6,r25,16
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 16, ctx.xer);
	// bgt cr6,0x9224c524
	if (ctx.cr6.gt) goto loc_9224C524;
	// cmplwi cr6,r25,0
	ctx.cr6.compare<uint32_t>(ctx.r25.u32, 0, ctx.xer);
	// beq cr6,0x9224c524
	if (ctx.cr6.eq) goto loc_9224C524;
	// addi r11,r25,-1
	ctx.r11.s64 = ctx.r25.s64 + -1;
	// and. r11,r11,r25
	ctx.r11.u64 = ctx.r11.u64 & ctx.r25.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c524
	if (!ctx.cr0.eq) goto loc_9224C524;
	// cmplw cr6,r24,r25
	ctx.cr6.compare<uint32_t>(ctx.r24.u32, ctx.r25.u32, ctx.xer);
	// bne cr6,0x9224c524
	if (!ctx.cr6.eq) goto loc_9224C524;
	// addi r11,r24,-1
	ctx.r11.s64 = ctx.r24.s64 + -1;
	// and. r10,r11,r31
	ctx.r10.u64 = ctx.r11.u64 & ctx.r31.u64;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne 0x9224c524
	if (!ctx.cr0.eq) goto loc_9224C524;
	// and. r11,r11,r29
	ctx.r11.u64 = ctx.r11.u64 & ctx.r29.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c524
	if (!ctx.cr0.eq) goto loc_9224C524;
	// cmplw cr6,r31,r29
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r29.u32, ctx.xer);
	// bne cr6,0x9224c4e8
	if (!ctx.cr6.eq) goto loc_9224C4E8;
	// mr r6,r30
	ctx.r6.u64 = ctx.r30.u64;
	// mr r5,r26
	ctx.r5.u64 = ctx.r26.u64;
	// mr r4,r23
	ctx.r4.u64 = ctx.r23.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9224c0d8
	ctx.lr = 0x9224C4E4;
	sub_9224C0D8(ctx, base);
	// b 0x9224c54c
	goto loc_9224C54C;
loc_9224C4E8:
	// subf. r11,r29,r31
	ctx.r11.u64 = ctx.r31.u64 - ctx.r29.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bge 0x9224c4f4
	if (!ctx.cr0.lt) goto loc_9224C4F4;
	// subf r11,r31,r29
	ctx.r11.u64 = ctx.r29.u64 - ctx.r31.u64;
loc_9224C4F4:
	// cmpwi cr6,r11,128
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 128, ctx.xer);
	// blt cr6,0x9224c524
	if (ctx.cr6.lt) goto loc_9224C524;
	// xor r11,r29,r31
	ctx.r11.u64 = ctx.r29.u64 ^ ctx.r31.u64;
	// clrlwi. r11,r11,28
	ctx.r11.u64 = ctx.r11.u32 & 0xF;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c524
	if (!ctx.cr0.eq) goto loc_9224C524;
	// mr r7,r30
	ctx.r7.u64 = ctx.r30.u64;
	// mr r6,r26
	ctx.r6.u64 = ctx.r26.u64;
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9224bd80
	ctx.lr = 0x9224C520;
	sub_9224BD80(ctx, base);
	// b 0x9224c54c
	goto loc_9224C54C;
loc_9224C524:
	// cmplwi cr6,r30,0
	ctx.cr6.compare<uint32_t>(ctx.r30.u32, 0, ctx.xer);
	// beq cr6,0x9224c54c
	if (ctx.cr6.eq) goto loc_9224C54C;
loc_9224C52C:
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9224bc28
	ctx.lr = 0x9224C53C;
	sub_9224BC28(ctx, base);
	// addic. r30,r30,-1
	ctx.xer.ca = ctx.r30.u32 > 0;
	ctx.r30.s64 = ctx.r30.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// add r31,r26,r31
	ctx.r31.u64 = ctx.r26.u64 + ctx.r31.u64;
	// add r29,r26,r29
	ctx.r29.u64 = ctx.r26.u64 + ctx.r29.u64;
	// bne 0x9224c52c
	if (!ctx.cr0.eq) goto loc_9224C52C;
loc_9224C54C:
	// addi r1,r1,160
	ctx.r1.s64 = ctx.r1.s64 + 160;
	// b 0x9205b4b4
	__restgprlr_23(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224C558) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b448
	ctx.lr = 0x9224C560;
	__savegprlr_16(ctx, base);
	// stwu r1,-224(r1)
	ea = -224 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r16,r8
	ctx.r16.u64 = ctx.r8.u64;
	// mr r18,r7
	ctx.r18.u64 = ctx.r7.u64;
	// lwz r7,316(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 316);
	// lis r8,-28160
	ctx.r8.s64 = -1845493760;
	// clrlwi r11,r7,26
	ctx.r11.u64 = ctx.r7.u32 & 0x3F;
	// addi r8,r8,6232
	ctx.r8.s64 = ctx.r8.s64 + 6232;
	// mr r22,r4
	ctx.r22.u64 = ctx.r4.u64;
	// mr r17,r5
	ctx.r17.u64 = ctx.r5.u64;
	// mr r4,r6
	ctx.r4.u64 = ctx.r6.u64;
	// mr r19,r9
	ctx.r19.u64 = ctx.r9.u64;
	// lbzx r8,r11,r8
	ctx.r8.u64 = REX_LOAD_U8(ctx.r11.u32 + ctx.r8.u32);
	// mr r20,r10
	ctx.r20.u64 = ctx.r10.u64;
	// cmplwi cr6,r11,49
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 49, ctx.xer);
	// bgt cr6,0x9224c5d4
	if (ctx.cr6.gt) goto loc_9224C5D4;
	// beq cr6,0x9224c5f4
	if (ctx.cr6.eq) goto loc_9224C5F4;
	// cmplwi cr6,r11,11
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 11, ctx.xer);
	// blt cr6,0x9224c608
	if (ctx.cr6.lt) goto loc_9224C608;
	// cmplwi cr6,r11,12
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 12, ctx.xer);
	// ble cr6,0x9224c5c4
	if (!ctx.cr6.gt) goto loc_9224C5C4;
	// cmplwi cr6,r11,17
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 17, ctx.xer);
	// ble cr6,0x9224c608
	if (!ctx.cr6.gt) goto loc_9224C608;
	// cmplwi cr6,r11,20
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 20, ctx.xer);
	// ble cr6,0x9224c5f4
	if (!ctx.cr6.gt) goto loc_9224C5F4;
	// b 0x9224c608
	goto loc_9224C608;
loc_9224C5C4:
	// addi r11,r9,1
	ctx.r11.s64 = ctx.r9.s64 + 1;
	// rlwinm r8,r8,1,0,30
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 1) & 0xFFFFFFFE;
	// rlwinm r19,r11,31,1,31
	ctx.r19.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 31) & 0x7FFFFFFF;
	// b 0x9224c608
	goto loc_9224C608;
loc_9224C5D4:
	// cmplwi cr6,r11,51
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 51, ctx.xer);
	// blt cr6,0x9224c608
	if (ctx.cr6.lt) goto loc_9224C608;
	// cmplwi cr6,r11,53
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 53, ctx.xer);
	// ble cr6,0x9224c5f4
	if (!ctx.cr6.gt) goto loc_9224C5F4;
	// cmplwi cr6,r11,57
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 57, ctx.xer);
	// ble cr6,0x9224c608
	if (!ctx.cr6.gt) goto loc_9224C608;
	// cmplwi cr6,r11,61
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 61, ctx.xer);
	// bgt cr6,0x9224c608
	if (ctx.cr6.gt) goto loc_9224C608;
loc_9224C5F4:
	// addi r11,r9,3
	ctx.r11.s64 = ctx.r9.s64 + 3;
	// addi r6,r10,3
	ctx.r6.s64 = ctx.r10.s64 + 3;
	// rlwinm r19,r11,30,2,31
	ctx.r19.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 30) & 0x3FFFFFFF;
	// rlwinm r20,r6,30,2,31
	ctx.r20.u64 = __builtin_rotateleft64(ctx.r6.u32 | (ctx.r6.u64 << 32), 30) & 0x3FFFFFFF;
	// rlwinm r8,r8,4,0,27
	ctx.r8.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 4) & 0xFFFFFFF0;
loc_9224C608:
	// srawi r11,r7,6
	ctx.xer.ca = (ctx.r7.s32 < 0) & ((ctx.r7.u32 & 0x3F) != 0);
	ctx.r11.s64 = ctx.r7.s32 >> 6;
	// clrlwi r11,r11,30
	ctx.r11.u64 = ctx.r11.u32 & 0x3;
	// cmplwi cr6,r11,1
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 1, ctx.xer);
	// blt cr6,0x9224c650
	if (ctx.cr6.lt) goto loc_9224C650;
	// beq cr6,0x9224c644
	if (ctx.cr6.eq) goto loc_9224C644;
	// cmplwi cr6,r11,3
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 3, ctx.xer);
	// blt cr6,0x9224c63c
	if (ctx.cr6.lt) goto loc_9224C63C;
	// beq cr6,0x9224c630
	if (ctx.cr6.eq) goto loc_9224C630;
	// li r23,0
	ctx.r23.s64 = 0;
	// b 0x9224c654
	goto loc_9224C654;
loc_9224C630:
	// lis r23,4
	ctx.r23.s64 = 262144;
	// ori r23,r23,2
	ctx.r23.u64 = ctx.r23.u64 | 2;
	// b 0x9224c654
	goto loc_9224C654;
loc_9224C63C:
	// lis r23,4
	ctx.r23.s64 = 262144;
	// b 0x9224c648
	goto loc_9224C648;
loc_9224C644:
	// lis r23,2
	ctx.r23.s64 = 131072;
loc_9224C648:
	// ori r23,r23,1
	ctx.r23.u64 = ctx.r23.u64 | 1;
	// b 0x9224c654
	goto loc_9224C654;
loc_9224C650:
	// rlwinm r23,r8,13,0,15
	ctx.r23.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 13) & 0xFFFF0000;
loc_9224C654:
	// rlwinm r11,r8,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r8.u32 | (ctx.r8.u64 << 32), 29) & 0x1FFFFFFF;
	// rlwinm r25,r23,16,16,31
	ctx.r25.u64 = __builtin_rotateleft64(ctx.r23.u32 | (ctx.r23.u64 << 32), 16) & 0xFFFF;
	// addi r7,r11,-1
	ctx.r7.s64 = ctx.r11.s64 + -1;
	// rlwinm r11,r22,3,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r22.u32 | (ctx.r22.u64 << 32), 3) & 0xFFFFFFF8;
	// twllei r8,0
	if (ctx.r8.s32 == 0 || ctx.r8.u32 < 0u) ppc_trap(ctx, base, 0);
	// divwu r6,r11,r8
	ctx.r6.u64 = uint32_t(ctx.r8.u32 ? ctx.r11.u32 / ctx.r8.u32 : 0);
	// addi r11,r25,-1
	ctx.r11.s64 = ctx.r25.s64 + -1;
	// cntlzw r11,r11
	ctx.r11.u64 = ctx.r11.u32 == 0 ? 32 : __builtin_clz(ctx.r11.u32);
	// subfic r11,r11,35
	ctx.xer.ca = ctx.r11.u32 <= 35;
	ctx.r11.u64 = static_cast<uint64_t>(35) - ctx.r11.u64;
	// and. r5,r7,r22
	ctx.r5.u64 = ctx.r7.u64 & ctx.r22.u64;
	ctx.cr0.compare<int32_t>(ctx.r5.s32, 0, ctx.xer);
	// srw r21,r8,r11
	ctx.r21.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r8.u32 >> (ctx.r11.u8 & 0x3F));
	// bne 0x9224c718
	if (!ctx.cr0.eq) goto loc_9224C718;
	// cmplw cr6,r22,r18
	ctx.cr6.compare<uint32_t>(ctx.r22.u32, ctx.r18.u32, ctx.xer);
	// bne cr6,0x9224c718
	if (!ctx.cr6.eq) goto loc_9224C718;
	// cmplwi cr6,r9,16
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 16, ctx.xer);
	// ble cr6,0x9224c718
	if (!ctx.cr6.gt) goto loc_9224C718;
	// cmplwi cr6,r10,16
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 16, ctx.xer);
	// ble cr6,0x9224c718
	if (!ctx.cr6.gt) goto loc_9224C718;
	// lwz r31,308(r1)
	ctx.r31.u64 = REX_LOAD_U32(ctx.r1.u32 + 308);
	// cmplwi cr6,r31,1
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 1, ctx.xer);
	// ble cr6,0x9224c6d4
	if (!ctx.cr6.gt) goto loc_9224C6D4;
	// and. r11,r7,r17
	ctx.r11.u64 = ctx.r7.u64 & ctx.r17.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224c6d4
	if (!ctx.cr0.eq) goto loc_9224C6D4;
	// cmplw cr6,r17,r16
	ctx.cr6.compare<uint32_t>(ctx.r17.u32, ctx.r16.u32, ctx.xer);
	// bne cr6,0x9224c6d4
	if (!ctx.cr6.eq) goto loc_9224C6D4;
	// mullw r11,r21,r6
	ctx.r11.s64 = int64_t(ctx.r21.s32) * int64_t(ctx.r6.s32);
	// mullw r11,r11,r20
	ctx.r11.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r20.s32);
	// mullw r7,r11,r31
	ctx.r7.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r31.s32);
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// bl 0x9224c3c8
	ctx.lr = 0x9224C6D0;
	sub_9224C3C8(ctx, base);
	// b 0x9224c780
	goto loc_9224C780;
loc_9224C6D4:
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r29,r4
	ctx.r29.u64 = ctx.r4.u64;
	// cmplwi cr6,r31,0
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, 0, ctx.xer);
	// beq cr6,0x9224c780
	if (ctx.cr6.eq) goto loc_9224C780;
	// mullw r11,r21,r6
	ctx.r11.s64 = int64_t(ctx.r21.s32) * int64_t(ctx.r6.s32);
	// mullw r28,r11,r20
	ctx.r28.s64 = int64_t(ctx.r11.s32) * int64_t(ctx.r20.s32);
loc_9224C6EC:
	// mr r7,r28
	ctx.r7.u64 = ctx.r28.u64;
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224c3c8
	ctx.lr = 0x9224C704;
	sub_9224C3C8(ctx, base);
	// addic. r31,r31,-1
	ctx.xer.ca = ctx.r31.u32 > 0;
	ctx.r31.s64 = ctx.r31.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// add r30,r30,r17
	ctx.r30.u64 = ctx.r30.u64 + ctx.r17.u64;
	// add r29,r29,r16
	ctx.r29.u64 = ctx.r29.u64 + ctx.r16.u64;
	// bne 0x9224c6ec
	if (!ctx.cr0.eq) goto loc_9224C6EC;
	// b 0x9224c780
	goto loc_9224C780;
loc_9224C718:
	// lwz r11,308(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 308);
	// mr r27,r3
	ctx.r27.u64 = ctx.r3.u64;
	// mr r26,r4
	ctx.r26.u64 = ctx.r4.u64;
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x9224c780
	if (ctx.cr6.eq) goto loc_9224C780;
	// mr r24,r11
	ctx.r24.u64 = ctx.r11.u64;
loc_9224C730:
	// mr r30,r27
	ctx.r30.u64 = ctx.r27.u64;
	// mr r29,r26
	ctx.r29.u64 = ctx.r26.u64;
	// cmplwi cr6,r20,0
	ctx.cr6.compare<uint32_t>(ctx.r20.u32, 0, ctx.xer);
	// beq cr6,0x9224c770
	if (ctx.cr6.eq) goto loc_9224C770;
	// mullw r28,r21,r19
	ctx.r28.s64 = int64_t(ctx.r21.s32) * int64_t(ctx.r19.s32);
	// mr r31,r20
	ctx.r31.u64 = ctx.r20.u64;
loc_9224C748:
	// mr r7,r28
	ctx.r7.u64 = ctx.r28.u64;
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// mr r5,r23
	ctx.r5.u64 = ctx.r23.u64;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224c3c8
	ctx.lr = 0x9224C760;
	sub_9224C3C8(ctx, base);
	// addic. r31,r31,-1
	ctx.xer.ca = ctx.r31.u32 > 0;
	ctx.r31.s64 = ctx.r31.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// add r30,r30,r22
	ctx.r30.u64 = ctx.r30.u64 + ctx.r22.u64;
	// add r29,r29,r18
	ctx.r29.u64 = ctx.r29.u64 + ctx.r18.u64;
	// bne 0x9224c748
	if (!ctx.cr0.eq) goto loc_9224C748;
loc_9224C770:
	// addic. r24,r24,-1
	ctx.xer.ca = ctx.r24.u32 > 0;
	ctx.r24.s64 = ctx.r24.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r24.s32, 0, ctx.xer);
	// add r27,r27,r17
	ctx.r27.u64 = ctx.r27.u64 + ctx.r17.u64;
	// add r26,r26,r16
	ctx.r26.u64 = ctx.r26.u64 + ctx.r16.u64;
	// bne 0x9224c730
	if (!ctx.cr0.eq) goto loc_9224C730;
loc_9224C780:
	// addi r1,r1,224
	ctx.r1.s64 = ctx.r1.s64 + 224;
	// b 0x9205b498
	__restgprlr_16(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224C788) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r10,-28126
	ctx.r10.s64 = -1843265536;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r10,r10,6616
	ctx.r10.s64 = ctx.r10.s64 + 6616;
	// lis r9,-28126
	ctx.r9.s64 = -1843265536;
	// lis r31,-28121
	ctx.r31.s64 = -1842937856;
	// stw r10,-1640(r11)
	REX_STORE_U32(ctx.r11.u32 + -1640, ctx.r10.u32);
	// addi r10,r9,6864
	ctx.r10.s64 = ctx.r9.s64 + 6864;
	// lwz r11,-1640(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + -1640);
	// stw r10,-1636(r31)
	REX_STORE_U32(ctx.r31.u32 + -1636, ctx.r10.u32);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x9224C7C4;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C7D8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r10,-28126
	ctx.r10.s64 = -1843265536;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r10,r10,6864
	ctx.r10.s64 = ctx.r10.s64 + 6864;
	// lis r9,-28126
	ctx.r9.s64 = -1843265536;
	// lis r31,-28121
	ctx.r31.s64 = -1842937856;
	// stw r10,-1636(r11)
	REX_STORE_U32(ctx.r11.u32 + -1636, ctx.r10.u32);
	// addi r10,r9,6616
	ctx.r10.s64 = ctx.r9.s64 + 6616;
	// lwz r11,-1636(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + -1636);
	// stw r10,-1640(r31)
	REX_STORE_U32(ctx.r31.u32 + -1640, ctx.r10.u32);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x9224C814;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C828) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-176(r1)
	ea = -176 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// clrlwi r11,r4,31
	ctx.r11.u64 = ctx.r4.u32 & 0x1;
	// stw r3,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r3.u32);
	// lis r10,-28123
	ctx.r10.s64 = -1843068928;
	// cmplwi cr6,r6,0
	ctx.cr6.compare<uint32_t>(ctx.r6.u32, 0, ctx.xer);
	// addi r10,r10,-14296
	ctx.r10.s64 = ctx.r10.s64 + -14296;
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// li r11,0
	ctx.r11.s64 = 0;
	// stw r10,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r10.u32);
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
	// beq cr6,0x9224c88c
	if (ctx.cr6.eq) goto loc_9224C88C;
	// mr r11,r5
	ctx.r11.u64 = ctx.r5.u64;
	// cmplwi cr6,r5,15
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 15, ctx.xer);
	// ble cr6,0x9224c86c
	if (!ctx.cr6.gt) goto loc_9224C86C;
	// li r11,15
	ctx.r11.s64 = 15;
loc_9224C86C:
	// stw r11,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r11.u32);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x9224c890
	if (ctx.cr6.eq) goto loc_9224C890;
	// mr r4,r6
	ctx.r4.u64 = ctx.r6.u64;
	// addi r3,r1,100
	ctx.r3.s64 = ctx.r1.s64 + 100;
	// rlwinm r5,r11,2,0,29
	ctx.r5.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// bl 0x9205baa0
	ctx.lr = 0x9224C888;
	sub_9205BAA0(ctx, base);
	// b 0x9224c890
	goto loc_9224C890;
loc_9224C88C:
	// stw r11,96(r1)
	REX_STORE_U32(ctx.r1.u32 + 96, ctx.r11.u32);
loc_9224C890:
	// addi r3,r1,80
	ctx.r3.s64 = ctx.r1.s64 + 80;
	// bl 0x9224f24c
	ctx.lr = 0x9224C898;
	__imp__RtlRaiseException(ctx, base);
	// addi r1,r1,176
	ctx.r1.s64 = ctx.r1.s64 + 176;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C8A8) {
	REX_FUNC_PROLOGUE();
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r3,1
	ctx.r3.s64 = 1;
	// stw r4,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r4.u32);
	// stw r5,4(r11)
	REX_STORE_U32(ctx.r11.u32 + 4, ctx.r5.u32);
	// stw r6,8(r11)
	REX_STORE_U32(ctx.r11.u32 + 8, ctx.r6.u32);
	// stw r7,12(r11)
	REX_STORE_U32(ctx.r11.u32 + 12, ctx.r7.u32);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C8C8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r11,r4
	ctx.r11.u64 = ctx.r4.u64;
	// mr r4,r5
	ctx.r4.u64 = ctx.r5.u64;
	// mr r9,r3
	ctx.r9.u64 = ctx.r3.u64;
	// mr r5,r6
	ctx.r5.u64 = ctx.r6.u64;
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x9224c91c
	if (!ctx.cr6.eq) goto loc_9224C91C;
loc_9224C8EC:
	// bl 0x9205f378
	ctx.lr = 0x9224C8F0;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224C914;
	sub_9205F228(ctx, base);
	// li r3,-1
	ctx.r3.s64 = -1;
	// b 0x9224c964
	goto loc_9224C964;
loc_9224C91C:
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// beq cr6,0x9224c8ec
	if (ctx.cr6.eq) goto loc_9224C8EC;
	// li r10,73
	ctx.r10.s64 = 73;
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
	// stw r11,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
	// stw r10,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r10.u32);
	// mr r10,r11
	ctx.r10.u64 = ctx.r11.u64;
loc_9224C938:
	// lbz r8,0(r11)
	ctx.r8.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// cmplwi cr6,r8,0
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, 0, ctx.xer);
	// bne cr6,0x9224c938
	if (!ctx.cr6.eq) goto loc_9224C938;
	// subf r11,r10,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r10.u64;
	// mr r6,r7
	ctx.r6.u64 = ctx.r7.u64;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// addi r3,r1,80
	ctx.r3.s64 = ctx.r1.s64 + 80;
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// mtctr r9
	ctx.ctr.u64 = ctx.r9.u64;
	// bctrl 
	ctx.lr = 0x9224C964;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
loc_9224C964:
	// addi r1,r1,128
	ctx.r1.s64 = ctx.r1.s64 + 128;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C978) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r5,32(r1)
	REX_STORE_U64(ctx.r1.u32 + 32, ctx.r5.u64);
	// std r6,40(r1)
	REX_STORE_U64(ctx.r1.u32 + 40, ctx.r6.u64);
	// std r7,48(r1)
	REX_STORE_U64(ctx.r1.u32 + 48, ctx.r7.u64);
	// std r8,56(r1)
	REX_STORE_U64(ctx.r1.u32 + 56, ctx.r8.u64);
	// std r9,64(r1)
	REX_STORE_U64(ctx.r1.u32 + 64, ctx.r9.u64);
	// std r10,72(r1)
	REX_STORE_U64(ctx.r1.u32 + 72, ctx.r10.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// addi r10,r1,80
	ctx.r10.s64 = ctx.r1.s64 + 80;
	// addi r9,r1,128
	ctx.r9.s64 = ctx.r1.s64 + 128;
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// mr r5,r4
	ctx.r5.u64 = ctx.r4.u64;
	// mr r4,r3
	ctx.r4.u64 = ctx.r3.u64;
	// li r6,0
	ctx.r6.s64 = 0;
	// addi r3,r11,-12648
	ctx.r3.s64 = ctx.r11.s64 + -12648;
	// stw r9,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r9.u32);
	// lwz r7,80(r1)
	ctx.r7.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// bl 0x9224c8c8
	ctx.lr = 0x9224C9C4;
	sub_9224C8C8(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224C9D8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b478
	ctx.lr = 0x9224C9E0;
	__savegprlr_28(ctx, base);
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r28,r4
	ctx.r28.u64 = ctx.r4.u64;
	// li r4,46
	ctx.r4.s64 = 46;
	// mr r30,r3
	ctx.r30.u64 = ctx.r3.u64;
	// mr r29,r5
	ctx.r29.u64 = ctx.r5.u64;
	// bl 0x9224e420
	ctx.lr = 0x9224C9F8;
	sub_9224E420(ctx, base);
	// addi r31,r3,1
	ctx.r31.s64 = ctx.r3.s64 + 1;
	// li r5,32
	ctx.r5.s64 = 32;
	// li r4,0
	ctx.r4.s64 = 0;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92069868
	ctx.lr = 0x9224CA0C;
	sub_92069868(ctx, base);
	// addi r3,r3,1
	ctx.r3.s64 = ctx.r3.s64 + 1;
	// cmplw cr6,r3,r29
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, ctx.r29.u32, ctx.xer);
	// blt cr6,0x9224ca20
	if (ctx.cr6.lt) goto loc_9224CA20;
	// li r3,-1
	ctx.r3.s64 = -1;
	// b 0x9224ca88
	goto loc_9224CA88;
loc_9224CA20:
	// li r6,32
	ctx.r6.s64 = 32;
	// li r5,8
	ctx.r5.s64 = 8;
	// addi r4,r1,80
	ctx.r4.s64 = ctx.r1.s64 + 80;
	// bl 0x9224e338
	ctx.lr = 0x9224CA30;
	sub_9224E338(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224ca50
	if (ctx.cr0.eq) goto loc_9224CA50;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224CA50;
	sub_9205F290(ctx, base);
loc_9224CA50:
	// subf r11,r31,r30
	ctx.r11.u64 = ctx.r30.u64 - ctx.r31.u64;
	// addi r5,r1,80
	ctx.r5.s64 = ctx.r1.s64 + 80;
	// add r4,r11,r28
	ctx.r4.u64 = ctx.r11.u64 + ctx.r28.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063860
	ctx.lr = 0x9224CA64;
	sub_92063860(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224ca84
	if (ctx.cr0.eq) goto loc_9224CA84;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224CA84;
	sub_9205F290(ctx, base);
loc_9224CA84:
	// li r3,0
	ctx.r3.s64 = 0;
loc_9224CA88:
	// addi r1,r1,128
	ctx.r1.s64 = ctx.r1.s64 + 128;
	// b 0x9205b4c8
	__restgprlr_28(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224CA98) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b46c
	ctx.lr = 0x9224CAA0;
	__savegprlr_25(ctx, base);
	// addi r31,r1,-176
	ctx.r31.s64 = ctx.r1.s64 + -176;
	// stwu r1,-176(r1)
	ea = -176 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r26,r3
	ctx.r26.u64 = ctx.r3.u64;
	// mr r25,r4
	ctx.r25.u64 = ctx.r4.u64;
	// cntlzw r11,r26
	ctx.r11.u64 = ctx.r26.u32 == 0 ? 32 : __builtin_clz(ctx.r26.u32);
	// li r27,0
	ctx.r27.s64 = 0;
	// stw r27,96(r31)
	REX_STORE_U32(ctx.r31.u32 + 96, ctx.r27.u32);
	// rlwinm r11,r11,27,31,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1;
	// stw r27,92(r31)
	REX_STORE_U32(ctx.r31.u32 + 92, ctx.r27.u32);
	// xori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 ^ 1;
	// cmpwi r11,0
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224cb00
	if (!ctx.cr0.eq) goto loc_9224CB00;
	// bl 0x9205f378
	ctx.lr = 0x9224CAD4;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224CAF8;
	sub_9205F228(ctx, base);
	// li r3,22
	ctx.r3.s64 = 22;
	// b 0x9224cd50
	goto loc_9224CD50;
loc_9224CB00:
	// li r3,2
	ctx.r3.s64 = 2;
	// stw r27,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r27.u32);
	// bl 0x92063310
	ctx.lr = 0x9224CB0C;
	sub_92063310(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224cb20
	if (!ctx.cr0.eq) goto loc_9224CB20;
	// bl 0x9205f378
	ctx.lr = 0x9224CB18;
	sub_9205F378(ctx, base);
	// lwz r3,0(r3)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r3.u32 + 0);
	// b 0x9224cd50
	goto loc_9224CD50;
loc_9224CB20:
	// li r3,2
	ctx.r3.s64 = 2;
	// bl 0x92063450
	ctx.lr = 0x9224CB28;
	sub_92063450(ctx, base);
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r30,r11,17220
	ctx.r30.s64 = ctx.r11.s64 + 17220;
	// lbz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r30.u32 + 0);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// li r4,20
	ctx.r4.s64 = 20;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bne 0x9224cc24
	if (!ctx.cr0.eq) goto loc_9224CC24;
	// lis r11,-28156
	ctx.r11.s64 = -1845231616;
	// addi r5,r11,9960
	ctx.r5.s64 = ctx.r11.s64 + 9960;
	// bl 0x92063860
	ctx.lr = 0x9224CB54;
	sub_92063860(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224cb74
	if (ctx.cr0.eq) goto loc_9224CB74;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224CB74;
	sub_9205F290(ctx, base);
loc_9224CB74:
	// lbz r11,2(r30)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r30.u32 + 2);
	// extsb r10,r11
	ctx.r10.s64 = ctx.r11.s8;
	// addi r11,r30,3
	ctx.r11.s64 = ctx.r30.s64 + 3;
	// stw r11,84(r31)
	REX_STORE_U32(ctx.r31.u32 + 84, ctx.r11.u32);
	// cmpwi cr6,r10,92
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 92, ctx.xer);
	// beq cr6,0x9224cba4
	if (ctx.cr6.eq) goto loc_9224CBA4;
	// cmpwi cr6,r10,47
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 47, ctx.xer);
	// beq cr6,0x9224cba4
	if (ctx.cr6.eq) goto loc_9224CBA4;
	// li r11,92
	ctx.r11.s64 = 92;
	// stb r11,3(r30)
	REX_STORE_U8(ctx.r30.u32 + 3, ctx.r11.u8);
	// addi r11,r30,4
	ctx.r11.s64 = ctx.r30.s64 + 4;
	// stw r11,84(r31)
	REX_STORE_U32(ctx.r31.u32 + 84, ctx.r11.u32);
loc_9224CBA4:
	// li r10,116
	ctx.r10.s64 = 116;
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// addi r29,r11,1
	ctx.r29.s64 = ctx.r11.s64 + 1;
	// stw r29,84(r31)
	REX_STORE_U32(ctx.r31.u32 + 84, ctx.r29.u32);
	// bl 0x921ef430
	ctx.lr = 0x9224CBB8;
	sub_921EF430(ctx, base);
	// li r6,32
	ctx.r6.s64 = 32;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// addi r11,r30,20
	ctx.r11.s64 = ctx.r30.s64 + 20;
	// subf r5,r29,r11
	ctx.r5.u64 = ctx.r11.u64 - ctx.r29.u64;
	// bl 0x9224e338
	ctx.lr = 0x9224CBCC;
	sub_9224E338(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224cbec
	if (ctx.cr0.eq) goto loc_9224CBEC;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224CBEC;
	sub_9205F290(ctx, base);
loc_9224CBEC:
	// lis r11,-28158
	ctx.r11.s64 = -1845362688;
	// addi r5,r11,-15964
	ctx.r5.s64 = ctx.r11.s64 + -15964;
	// li r4,20
	ctx.r4.s64 = 20;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224e0a0
	ctx.lr = 0x9224CC00;
	sub_9224E0A0(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224cc38
	if (ctx.cr0.eq) goto loc_9224CC38;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224CC20;
	sub_9205F290(ctx, base);
	// b 0x9224cc38
	goto loc_9224CC38;
loc_9224CC24:
	// lis r5,32767
	ctx.r5.s64 = 2147418112;
	// ori r5,r5,65535
	ctx.r5.u64 = ctx.r5.u64 | 65535;
	// bl 0x9224c9d8
	ctx.lr = 0x9224CC30;
	sub_9224C9D8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224cd28
	if (!ctx.cr0.eq) goto loc_9224CD28;
loc_9224CC38:
	// bl 0x92060e78
	ctx.lr = 0x9224CC3C;
	sub_92060E78(ctx, base);
	// mr. r29,r3
	ctx.r29.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r29.s32, 0, ctx.xer);
	// stw r29,88(r31)
	REX_STORE_U32(ctx.r31.u32 + 88, ctx.r29.u32);
	// bne 0x9224cc54
	if (!ctx.cr0.eq) goto loc_9224CC54;
	// li r11,24
	ctx.r11.s64 = 24;
	// stw r11,96(r31)
	REX_STORE_U32(ctx.r31.u32 + 96, ctx.r11.u32);
	// b 0x9224cd2c
	goto loc_9224CD2C;
loc_9224CC54:
	// li r11,1
	ctx.r11.s64 = 1;
	// stw r11,92(r31)
	REX_STORE_U32(ctx.r31.u32 + 92, ctx.r11.u32);
	// bl 0x9205f378
	ctx.lr = 0x9224CC60;
	sub_9205F378(ctx, base);
	// lwz r28,0(r3)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r3.u32 + 0);
	// bl 0x9205f378
	ctx.lr = 0x9224CC68;
	sub_9205F378(ctx, base);
	// stw r27,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r27.u32);
loc_9224CC6C:
	// li r7,384
	ctx.r7.s64 = 384;
	// mr r6,r25
	ctx.r6.u64 = ctx.r25.u64;
	// lis r5,0
	ctx.r5.s64 = 0;
	// ori r5,r5,34114
	ctx.r5.u64 = ctx.r5.u64 | 34114;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// addi r3,r31,80
	ctx.r3.s64 = ctx.r31.s64 + 80;
	// bl 0x920663d0
	ctx.lr = 0x9224CC88;
	sub_920663D0(ctx, base);
	// cmpwi cr6,r3,17
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 17, ctx.xer);
	// bne cr6,0x9224ccb4
	if (!ctx.cr6.eq) goto loc_9224CCB4;
	// lis r5,32767
	ctx.r5.s64 = 2147418112;
	// ori r5,r5,65535
	ctx.r5.u64 = ctx.r5.u64 | 65535;
	// li r4,20
	ctx.r4.s64 = 20;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224c9d8
	ctx.lr = 0x9224CCA4;
	sub_9224C9D8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224ccb4
	if (!ctx.cr0.eq) goto loc_9224CCB4;
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// b 0x9224cc6c
	goto loc_9224CC6C;
loc_9224CCB4:
	// bl 0x9205f378
	ctx.lr = 0x9224CCB8;
	sub_9205F378(ctx, base);
	// lwz r11,0(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 0);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224cccc
	if (!ctx.cr6.eq) goto loc_9224CCCC;
	// bl 0x9205f378
	ctx.lr = 0x9224CCC8;
	sub_9205F378(ctx, base);
	// stw r28,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r28.u32);
loc_9224CCCC:
	// lwz r11,80(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// cmpwi cr6,r11,-1
	ctx.cr6.compare<int32_t>(ctx.r11.s32, -1, ctx.xer);
	// beq cr6,0x9224cd2c
	if (ctx.cr6.eq) goto loc_9224CD2C;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224e5c0
	ctx.lr = 0x9224CCE0;
	sub_9224E5C0(ctx, base);
	// stw r3,28(r29)
	REX_STORE_U32(ctx.r29.u32 + 28, ctx.r3.u32);
	// rotlwi r11,r3,0
	ctx.r11.u64 = __builtin_rotateleft32(ctx.r3.u32, 0);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne cr6,0x9224ccfc
	if (!ctx.cr6.eq) goto loc_9224CCFC;
	// lwz r3,80(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// bl 0x9205f710
	ctx.lr = 0x9224CCF8;
	sub_9205F710(ctx, base);
	// b 0x9224cd2c
	goto loc_9224CD2C;
loc_9224CCFC:
	// stw r27,4(r29)
	REX_STORE_U32(ctx.r29.u32 + 4, ctx.r27.u32);
	// stw r27,0(r29)
	REX_STORE_U32(ctx.r29.u32 + 0, ctx.r27.u32);
	// stw r27,8(r29)
	REX_STORE_U32(ctx.r29.u32 + 8, ctx.r27.u32);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// lwz r11,20(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 20);
	// ori r11,r11,128
	ctx.r11.u64 = ctx.r11.u64 | 128;
	// stw r11,12(r29)
	REX_STORE_U32(ctx.r29.u32 + 12, ctx.r11.u32);
	// lwz r11,80(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// stw r11,16(r29)
	REX_STORE_U32(ctx.r29.u32 + 16, ctx.r11.u32);
	// stw r29,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r29.u32);
	// b 0x9224cd2c
	goto loc_9224CD2C;
loc_9224CD28:
	// lwz r29,88(r31)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r31.u32 + 88);
loc_9224CD2C:
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// addi r12,r31,176
	ctx.r12.s64 = ctx.r31.s64 + 176;
	// bl 0x9224cd78
	ctx.lr = 0x9224CD38;
	sub_9224CD78(ctx, base);
	// lwz r30,96(r31)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r31.u32 + 96);
	// cmpwi cr6,r30,0
	ctx.cr6.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// beq cr6,0x9224cd4c
	if (ctx.cr6.eq) goto loc_9224CD4C;
	// bl 0x9205f378
	ctx.lr = 0x9224CD48;
	sub_9205F378(ctx, base);
	// stw r30,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r30.u32);
loc_9224CD4C:
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
loc_9224CD50:
	// addi r1,r31,176
	ctx.r1.s64 = ctx.r31.s64 + 176;
	// b 0x9205b4bc
	__restgprlr_25(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224CD58) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// std r31,-8(r1)
	REX_STORE_U64(ctx.r1.u32 + -8, ctx.r31.u64);
	// addi r31,r12,-176
	ctx.r31.s64 = ctx.r12.s64 + -176;
	// std r29,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r29.u64);
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-24(r1)
	REX_STORE_U32(ctx.r1.u32 + -24, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lwz r29,88(r31)
	ctx.r29.u64 = REX_LOAD_U32(ctx.r31.u32 + 88);
	// b 0x9224cd90
	goto loc_9224CD90;
loc_9224CD90:
	// lwz r11,92(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 92);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq cr6,0x9224cda4
	if (ctx.cr6.eq) goto loc_9224CDA4;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x9205ff08
	ctx.lr = 0x9224CDA4;
	sub_9205FF08(ctx, base);
loc_9224CDA4:
	// li r3,2
	ctx.r3.s64 = 2;
	// bl 0x920632f0
	ctx.lr = 0x9224CDAC;
	sub_920632F0(ctx, base);
	// lwz r1,0(r1)
	ctx.r1.u64 = REX_LOAD_U32(ctx.r1.u32 + 0);
	// ld r31,-8(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -8);
	// ld r29,-16(r1)
	ctx.r29.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// lwz r12,-24(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -24);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224CD78) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// std r31,-8(r1)
	REX_STORE_U64(ctx.r1.u32 + -8, ctx.r31.u64);
	// addi r31,r12,-176
	ctx.r31.s64 = ctx.r12.s64 + -176;
	// std r29,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r29.u64);
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-24(r1)
	REX_STORE_U32(ctx.r1.u32 + -24, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lwz r11,92(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 92);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq cr6,0x9224cda4
	if (ctx.cr6.eq) goto loc_9224CDA4;
	// mr r3,r29
	ctx.r3.u64 = ctx.r29.u64;
	// bl 0x9205ff08
	ctx.lr = 0x9224CDA4;
	sub_9205FF08(ctx, base);
loc_9224CDA4:
	// li r3,2
	ctx.r3.s64 = 2;
	// bl 0x920632f0
	ctx.lr = 0x9224CDAC;
	sub_920632F0(ctx, base);
	// lwz r1,0(r1)
	ctx.r1.u64 = REX_LOAD_U32(ctx.r1.u32 + 0);
	// ld r31,-8(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -8);
	// ld r29,-16(r1)
	ctx.r29.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// lwz r12,-24(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -24);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224CDC8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// li r11,0
	ctx.r11.s64 = 0;
	// li r4,64
	ctx.r4.s64 = 64;
	// addi r3,r1,80
	ctx.r3.s64 = ctx.r1.s64 + 80;
	// stw r11,80(r1)
	REX_STORE_U32(ctx.r1.u32 + 80, ctx.r11.u32);
	// bl 0x9224ca98
	ctx.lr = 0x9224CDE8;
	sub_9224CA98(ctx, base);
	// lwz r3,80(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 80);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224CE00) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b478
	ctx.lr = 0x9224CE08;
	__savegprlr_28(ctx, base);
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r31,r4
	ctx.r31.u64 = ctx.r4.u64;
	// mr r30,r5
	ctx.r30.u64 = ctx.r5.u64;
	// mr r29,r6
	ctx.r29.u64 = ctx.r6.u64;
	// mr r28,r7
	ctx.r28.u64 = ctx.r7.u64;
	// lwz r11,0(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// cmplw cr6,r3,r11
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, ctx.r11.u32, ctx.xer);
	// bne cr6,0x9224ce8c
	if (!ctx.cr6.eq) goto loc_9224CE8C;
	// lwz r3,0(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// cmplw cr6,r3,r29
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, ctx.r29.u32, ctx.xer);
	// bne cr6,0x9224ce6c
	if (!ctx.cr6.eq) goto loc_9224CE6C;
	// rlwinm r3,r11,1,0,30
	ctx.r3.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// bl 0x92063130
	ctx.lr = 0x9224CE3C;
	sub_92063130(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// stw r3,0(r30)
	REX_STORE_U32(ctx.r30.u32 + 0, ctx.r3.u32);
	// bne 0x9224ce50
	if (!ctx.cr0.eq) goto loc_9224CE50;
loc_9224CE48:
	// li r3,0
	ctx.r3.s64 = 0;
	// b 0x9224ce90
	goto loc_9224CE90;
loc_9224CE50:
	// li r11,1
	ctx.r11.s64 = 1;
	// mr r4,r29
	ctx.r4.u64 = ctx.r29.u64;
	// stw r11,0(r28)
	REX_STORE_U32(ctx.r28.u32 + 0, ctx.r11.u32);
	// lwz r5,0(r31)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// lwz r3,0(r30)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// bl 0x9205b680
	ctx.lr = 0x9224CE68;
	sub_9205B680(ctx, base);
	// b 0x9224ce80
	goto loc_9224CE80;
loc_9224CE6C:
	// rlwinm r4,r11,1,0,30
	ctx.r4.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// bl 0x92062fc8
	ctx.lr = 0x9224CE74;
	sub_92062FC8(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224ce48
	if (ctx.cr0.eq) goto loc_9224CE48;
	// stw r3,0(r30)
	REX_STORE_U32(ctx.r30.u32 + 0, ctx.r3.u32);
loc_9224CE80:
	// lwz r11,0(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// rlwinm r11,r11,1,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
loc_9224CE8C:
	// li r3,1
	ctx.r3.s64 = 1;
loc_9224CE90:
	// addi r1,r1,128
	ctx.r1.s64 = ctx.r1.s64 + 128;
	// b 0x9205b4c8
	__restgprlr_28(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224CE98) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b440
	ctx.lr = 0x9224CEA0;
	__savegprlr_14(ctx, base);
	// stwu r1,-688(r1)
	ea = -688 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// addi r11,r1,176
	ctx.r11.s64 = ctx.r1.s64 + 176;
	// stw r6,732(r1)
	REX_STORE_U32(ctx.r1.u32 + 732, ctx.r6.u32);
	// mr r28,r4
	ctx.r28.u64 = ctx.r4.u64;
	// li r23,0
	ctx.r23.s64 = 0;
	// mr r26,r3
	ctx.r26.u64 = ctx.r3.u64;
	// cmplwi cr6,r28,0
	ctx.cr6.compare<uint32_t>(ctx.r28.u32, 0, ctx.xer);
	// stw r11,84(r1)
	REX_STORE_U32(ctx.r1.u32 + 84, ctx.r11.u32);
	// li r11,350
	ctx.r11.s64 = 350;
	// stw r28,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r28.u32);
	// stw r23,100(r1)
	REX_STORE_U32(ctx.r1.u32 + 100, ctx.r23.u32);
	// sth r23,96(r1)
	REX_STORE_U16(ctx.r1.u32 + 96, ctx.r23.u16);
	// stw r11,104(r1)
	REX_STORE_U32(ctx.r1.u32 + 104, ctx.r11.u32);
	// bne cr6,0x9224cf08
	if (!ctx.cr6.eq) goto loc_9224CF08;
loc_9224CED8:
	// bl 0x9205f378
	ctx.lr = 0x9224CEDC;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224CF00;
	sub_9205F228(ctx, base);
loc_9224CF00:
	// li r3,-1
	ctx.r3.s64 = -1;
	// b 0x9224e094
	goto loc_9224E094;
loc_9224CF08:
	// cmplwi cr6,r26,0
	ctx.cr6.compare<uint32_t>(ctx.r26.u32, 0, ctx.xer);
	// beq cr6,0x9224ced8
	if (ctx.cr6.eq) goto loc_9224CED8;
	// lwz r11,12(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 12);
	// rlwinm. r11,r11,0,25,25
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0x40;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224cfec
	if (!ctx.cr0.eq) goto loc_9224CFEC;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CF24;
	sub_9205F888(ctx, base);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// cmpwi cr6,r3,-1
	ctx.cr6.compare<int32_t>(ctx.r3.s32, -1, ctx.xer);
	// addi r30,r11,17312
	ctx.r30.s64 = ctx.r11.s64 + 17312;
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r29,r11,2132
	ctx.r29.s64 = ctx.r11.s64 + 2132;
	// beq cr6,0x9224cf7c
	if (ctx.cr6.eq) goto loc_9224CF7C;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CF44;
	sub_9205F888(ctx, base);
	// cmpwi cr6,r3,-2
	ctx.cr6.compare<int32_t>(ctx.r3.s32, -2, ctx.xer);
	// beq cr6,0x9224cf7c
	if (ctx.cr6.eq) goto loc_9224CF7C;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CF54;
	sub_9205F888(ctx, base);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CF60;
	sub_9205F888(ctx, base);
	// srawi r11,r31,5
	ctx.xer.ca = (ctx.r31.s32 < 0) & ((ctx.r31.u32 & 0x1F) != 0);
	ctx.r11.s64 = ctx.r31.s32 >> 5;
	// clrlwi r10,r3,27
	ctx.r10.u64 = ctx.r3.u32 & 0x1F;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// mulli r10,r10,44
	ctx.r10.s64 = static_cast<int64_t>(ctx.r10.u64 * static_cast<uint64_t>(44));
	// lwzx r11,r11,r30
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r30.u32);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// b 0x9224cf80
	goto loc_9224CF80;
loc_9224CF7C:
	// mr r11,r29
	ctx.r11.u64 = ctx.r29.u64;
loc_9224CF80:
	// lbz r11,40(r11)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r11.u32 + 40);
	// rlwinm. r11,r11,0,0,30
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 0) & 0xFFFFFFFE;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224ced8
	if (!ctx.cr0.eq) goto loc_9224CED8;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CF94;
	sub_9205F888(ctx, base);
	// cmpwi cr6,r3,-1
	ctx.cr6.compare<int32_t>(ctx.r3.s32, -1, ctx.xer);
	// beq cr6,0x9224cfdc
	if (ctx.cr6.eq) goto loc_9224CFDC;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CFA4;
	sub_9205F888(ctx, base);
	// cmpwi cr6,r3,-2
	ctx.cr6.compare<int32_t>(ctx.r3.s32, -2, ctx.xer);
	// beq cr6,0x9224cfdc
	if (ctx.cr6.eq) goto loc_9224CFDC;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CFB4;
	sub_9205F888(ctx, base);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205f888
	ctx.lr = 0x9224CFC0;
	sub_9205F888(ctx, base);
	// srawi r11,r31,5
	ctx.xer.ca = (ctx.r31.s32 < 0) & ((ctx.r31.u32 & 0x1F) != 0);
	ctx.r11.s64 = ctx.r31.s32 >> 5;
	// clrlwi r10,r3,27
	ctx.r10.u64 = ctx.r3.u32 & 0x1F;
	// rlwinm r11,r11,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 2) & 0xFFFFFFFC;
	// mulli r10,r10,44
	ctx.r10.s64 = static_cast<int64_t>(ctx.r10.u64 * static_cast<uint64_t>(44));
	// lwzx r11,r11,r30
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r30.u32);
	// add r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 + ctx.r10.u64;
	// b 0x9224cfe0
	goto loc_9224CFE0;
loc_9224CFDC:
	// mr r11,r29
	ctx.r11.u64 = ctx.r29.u64;
loc_9224CFE0:
	// lbz r11,40(r11)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r11.u32 + 40);
	// clrlwi. r11,r11,31
	ctx.r11.u64 = ctx.r11.u32 & 0x1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224ced8
	if (!ctx.cr0.eq) goto loc_9224CED8;
loc_9224CFEC:
	// lbz r3,0(r28)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r28.u32 + 0);
	// mr r14,r23
	ctx.r14.u64 = ctx.r23.u64;
	// stb r23,80(r1)
	REX_STORE_U8(ctx.r1.u32 + 80, ctx.r23.u8);
	// stw r23,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r23.u32);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224e090
	if (ctx.cr0.eq) goto loc_9224E090;
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// lwz r19,716(r1)
	ctx.r19.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
	// addi r11,r11,2408
	ctx.r11.s64 = ctx.r11.s64 + 2408;
	// stw r11,128(r1)
	REX_STORE_U32(ctx.r1.u32 + 128, ctx.r11.u32);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r11,r11,640
	ctx.r11.s64 = ctx.r11.s64 + 640;
	// stw r11,132(r1)
	REX_STORE_U32(ctx.r1.u32 + 132, ctx.r11.u32);
loc_9224D020:
	// bl 0x920636b8
	ctx.lr = 0x9224D024;
	sub_920636B8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224d0a0
	if (ctx.cr0.eq) goto loc_9224D0A0;
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
loc_9224D030:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d058
	if (ctx.cr0.lt) goto loc_9224D058;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r31,0(r11)
	ctx.r31.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d064
	goto loc_9224D064;
loc_9224D058:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D060;
	sub_9205FF58(ctx, base);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
loc_9224D064:
	// clrlwi r3,r31,24
	ctx.r3.u64 = ctx.r31.u32 & 0xFF;
	// bl 0x920636b8
	ctx.lr = 0x9224D06C;
	sub_920636B8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224d030
	if (!ctx.cr0.eq) goto loc_9224D030;
	// cmpwi cr6,r31,-1
	ctx.cr6.compare<int32_t>(ctx.r31.s32, -1, ctx.xer);
	// beq cr6,0x9224d088
	if (ctx.cr6.eq) goto loc_9224D088;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224D088;
	sub_921F5E20(ctx, base);
loc_9224D088:
	// addi r19,r19,1
	ctx.r19.s64 = ctx.r19.s64 + 1;
	// lbz r3,0(r19)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// bl 0x920636b8
	ctx.lr = 0x9224D094;
	sub_920636B8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224d088
	if (!ctx.cr0.eq) goto loc_9224D088;
	// b 0x9224e024
	goto loc_9224E024;
loc_9224D0A0:
	// lbz r11,0(r19)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// cmplwi cr6,r11,37
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 37, ctx.xer);
	// bne cr6,0x9224df5c
	if (!ctx.cr6.eq) goto loc_9224DF5C;
	// li r22,0
	ctx.r22.s64 = 0;
	// li r27,0
	ctx.r27.s64 = 0;
	// li r18,0
	ctx.r18.s64 = 0;
	// li r17,0
	ctx.r17.s64 = 0;
	// li r16,0
	ctx.r16.s64 = 0;
	// li r25,0
	ctx.r25.s64 = 0;
	// li r20,0
	ctx.r20.s64 = 0;
	// li r29,0
	ctx.r29.s64 = 0;
	// li r30,0
	ctx.r30.s64 = 0;
	// li r24,0
	ctx.r24.s64 = 0;
	// li r28,0
	ctx.r28.s64 = 0;
	// li r15,1
	ctx.r15.s64 = 1;
	// li r21,0
	ctx.r21.s64 = 0;
loc_9224D0E0:
	// addi r19,r19,1
	ctx.r19.s64 = ctx.r19.s64 + 1;
	// lbz r31,0(r19)
	ctx.r31.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063678
	ctx.lr = 0x9224D0F0;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224d10c
	if (ctx.cr0.eq) goto loc_9224D10C;
	// mulli r11,r16,10
	ctx.r11.s64 = static_cast<int64_t>(ctx.r16.u64 * static_cast<uint64_t>(10));
	// add r11,r11,r31
	ctx.r11.u64 = ctx.r11.u64 + ctx.r31.u64;
	// addi r17,r17,1
	ctx.r17.s64 = ctx.r17.s64 + 1;
	// addi r16,r11,-48
	ctx.r16.s64 = ctx.r11.s64 + -48;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D10C:
	// cmpwi cr6,r31,78
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 78, ctx.xer);
	// bgt cr6,0x9224d1cc
	if (ctx.cr6.gt) goto loc_9224D1CC;
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmpwi cr6,r31,42
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 42, ctx.xer);
	// beq cr6,0x9224d1c0
	if (ctx.cr6.eq) goto loc_9224D1C0;
	// cmpwi cr6,r31,70
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 70, ctx.xer);
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmpwi cr6,r31,73
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 73, ctx.xer);
	// beq cr6,0x9224d144
	if (ctx.cr6.eq) goto loc_9224D144;
	// cmpwi cr6,r31,76
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 76, ctx.xer);
	// bne cr6,0x9224d1e4
	if (!ctx.cr6.eq) goto loc_9224D1E4;
	// addi r11,r15,1
	ctx.r11.s64 = ctx.r15.s64 + 1;
	// extsb r15,r11
	ctx.r15.s64 = ctx.r11.s8;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D144:
	// lbz r10,1(r19)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r19.u32 + 1);
	// cmplwi cr6,r10,54
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 54, ctx.xer);
	// bne cr6,0x9224d174
	if (!ctx.cr6.eq) goto loc_9224D174;
	// addi r11,r19,2
	ctx.r11.s64 = ctx.r19.s64 + 2;
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// cmplwi cr6,r9,52
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 52, ctx.xer);
	// bne cr6,0x9224d174
	if (!ctx.cr6.eq) goto loc_9224D174;
loc_9224D160:
	// mr r19,r11
	ctx.r19.u64 = ctx.r11.u64;
	// li r11,0
	ctx.r11.s64 = 0;
	// addi r21,r21,1
	ctx.r21.s64 = ctx.r21.s64 + 1;
	// std r11,120(r1)
	REX_STORE_U64(ctx.r1.u32 + 120, ctx.r11.u64);
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D174:
	// cmplwi cr6,r10,51
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 51, ctx.xer);
	// bne cr6,0x9224d194
	if (!ctx.cr6.eq) goto loc_9224D194;
	// addi r11,r19,2
	ctx.r11.s64 = ctx.r19.s64 + 2;
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// cmplwi cr6,r9,50
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 50, ctx.xer);
	// bne cr6,0x9224d194
	if (!ctx.cr6.eq) goto loc_9224D194;
	// mr r19,r11
	ctx.r19.u64 = ctx.r11.u64;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D194:
	// cmplwi cr6,r10,100
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 100, ctx.xer);
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmplwi cr6,r10,105
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 105, ctx.xer);
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmplwi cr6,r10,111
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 111, ctx.xer);
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmplwi cr6,r10,120
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 120, ctx.xer);
	// beq cr6,0x9224d220
	if (ctx.cr6.eq) goto loc_9224D220;
	// cmplwi cr6,r10,88
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 88, ctx.xer);
	// bne cr6,0x9224d1e4
	if (!ctx.cr6.eq) goto loc_9224D1E4;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D1C0:
	// addi r11,r29,1
	ctx.r11.s64 = ctx.r29.s64 + 1;
	// extsb r29,r11
	ctx.r29.s64 = ctx.r11.s8;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D1CC:
	// cmpwi cr6,r31,104
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 104, ctx.xer);
	// beq cr6,0x9224d210
	if (ctx.cr6.eq) goto loc_9224D210;
	// cmpwi cr6,r31,108
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 108, ctx.xer);
	// beq cr6,0x9224d1f0
	if (ctx.cr6.eq) goto loc_9224D1F0;
	// cmpwi cr6,r31,119
	ctx.cr6.compare<int32_t>(ctx.r31.s32, 119, ctx.xer);
	// beq cr6,0x9224d208
	if (ctx.cr6.eq) goto loc_9224D208;
loc_9224D1E4:
	// addi r11,r30,1
	ctx.r11.s64 = ctx.r30.s64 + 1;
	// extsb r30,r11
	ctx.r30.s64 = ctx.r11.s8;
	// b 0x9224d220
	goto loc_9224D220;
loc_9224D1F0:
	// addi r11,r19,1
	ctx.r11.s64 = ctx.r19.s64 + 1;
	// lbz r10,0(r11)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// cmplwi cr6,r10,108
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 108, ctx.xer);
	// beq cr6,0x9224d160
	if (ctx.cr6.eq) goto loc_9224D160;
	// addi r11,r15,1
	ctx.r11.s64 = ctx.r15.s64 + 1;
	// extsb r15,r11
	ctx.r15.s64 = ctx.r11.s8;
loc_9224D208:
	// addi r11,r28,1
	ctx.r11.s64 = ctx.r28.s64 + 1;
	// b 0x9224d21c
	goto loc_9224D21C;
loc_9224D210:
	// addi r10,r15,-1
	ctx.r10.s64 = ctx.r15.s64 + -1;
	// addi r11,r28,-1
	ctx.r11.s64 = ctx.r28.s64 + -1;
	// extsb r15,r10
	ctx.r15.s64 = ctx.r10.s8;
loc_9224D21C:
	// extsb r28,r11
	ctx.r28.s64 = ctx.r11.s8;
loc_9224D220:
	// extsb. r11,r30
	ctx.r11.s64 = ctx.r30.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224d0e0
	if (ctx.cr0.eq) goto loc_9224D0E0;
	// extsb. r11,r29
	ctx.r11.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r19,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r19.u32);
	// stw r11,108(r1)
	REX_STORE_U32(ctx.r1.u32 + 108, ctx.r11.u32);
	// bne 0x9224d258
	if (!ctx.cr0.eq) goto loc_9224D258;
	// lwz r11,732(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 732);
	// addi r10,r11,7
	ctx.r10.s64 = ctx.r11.s64 + 7;
	// stw r11,136(r1)
	REX_STORE_U32(ctx.r1.u32 + 136, ctx.r11.u32);
	// rlwinm r11,r10,0,0,28
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r10.u32 | (ctx.r10.u64 << 32), 0) & 0xFFFFFFF8;
	// addi r11,r11,8
	ctx.r11.s64 = ctx.r11.s64 + 8;
	// stw r11,732(r1)
	REX_STORE_U32(ctx.r1.u32 + 732, ctx.r11.u32);
	// lwz r11,-4(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + -4);
	// b 0x9224d25c
	goto loc_9224D25C;
loc_9224D258:
	// li r11,0
	ctx.r11.s64 = 0;
loc_9224D25C:
	// stw r11,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r11.u32);
	// li r29,0
	ctx.r29.s64 = 0;
	// extsb. r11,r28
	ctx.r11.s64 = ctx.r28.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224d288
	if (!ctx.cr0.eq) goto loc_9224D288;
	// lbz r11,0(r19)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// cmplwi cr6,r11,83
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 83, ctx.xer);
	// beq cr6,0x9224d284
	if (ctx.cr6.eq) goto loc_9224D284;
	// cmplwi cr6,r11,67
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 67, ctx.xer);
	// li r28,-1
	ctx.r28.s64 = -1;
	// bne cr6,0x9224d288
	if (!ctx.cr6.eq) goto loc_9224D288;
loc_9224D284:
	// li r28,1
	ctx.r28.s64 = 1;
loc_9224D288:
	// lwz r10,716(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
	// lbz r11,0(r10)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// ori r19,r11,32
	ctx.r19.u64 = ctx.r11.u64 | 32;
	// cmpwi cr6,r19,110
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 110, ctx.xer);
	// beq cr6,0x9224d338
	if (ctx.cr6.eq) goto loc_9224D338;
	// cmpwi cr6,r19,99
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 99, ctx.xer);
	// beq cr6,0x9224d2f8
	if (ctx.cr6.eq) goto loc_9224D2F8;
	// cmpwi cr6,r19,123
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 123, ctx.xer);
	// beq cr6,0x9224d2f8
	if (ctx.cr6.eq) goto loc_9224D2F8;
loc_9224D2AC:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d2d4
	if (ctx.cr0.lt) goto loc_9224D2D4;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r31,0(r11)
	ctx.r31.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d2e0
	goto loc_9224D2E0;
loc_9224D2D4:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D2DC;
	sub_9205FF58(ctx, base);
	// mr r31,r3
	ctx.r31.u64 = ctx.r3.u64;
loc_9224D2E0:
	// clrlwi r3,r31,24
	ctx.r3.u64 = ctx.r31.u32 & 0xFF;
	// bl 0x920636b8
	ctx.lr = 0x9224D2E8;
	sub_920636B8(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224d2ac
	if (!ctx.cr0.eq) goto loc_9224D2AC;
	// mr r23,r31
	ctx.r23.u64 = ctx.r31.u64;
	// b 0x9224d32c
	goto loc_9224D32C;
loc_9224D2F8:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d320
	if (ctx.cr0.lt) goto loc_9224D320;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d32c
	goto loc_9224D32C;
loc_9224D320:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D328;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D32C:
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224e058
	if (ctx.cr6.eq) goto loc_9224E058;
	// lwz r10,716(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
loc_9224D338:
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d348
	if (ctx.cr6.eq) goto loc_9224D348;
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// beq cr6,0x9224e044
	if (ctx.cr6.eq) goto loc_9224E044;
loc_9224D348:
	// addi r11,r19,-99
	ctx.r11.s64 = ctx.r19.s64 + -99;
	// cmplwi cr6,r11,24
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 24, ctx.xer);
	// bgt cr6,0x9224df10
	if (ctx.cr6.gt) goto loc_9224DF10;
	// lis r12,-28156
	ctx.r12.s64 = -1845231616;
	// addi r12,r12,9968
	ctx.r12.s64 = ctx.r12.s64 + 9968;
	// rlwinm r0,r11,1,0,30
	ctx.r0.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 1) & 0xFFFFFFFE;
	// lhzx r0,r12,r0
	ctx.r0.u64 = REX_LOAD_U16(ctx.r12.u32 + ctx.r0.u32);
	// lis r12,-28123
	ctx.r12.s64 = -1843068928;
	// addi r12,r12,-11396
	ctx.r12.s64 = ctx.r12.s64 + -11396;
	// add r12,r12,r0
	ctx.r12.u64 = ctx.r12.u64 + ctx.r0.u64;
	// mtctr r12
	ctx.ctr.u64 = ctx.r12.u64;
	// nop 
	// bctr 
	switch (ctx.r11.u32) {
	case 0:
		goto loc_9224D37C;
	case 1:
		goto loc_9224D80C;
	case 2:
		goto loc_9224DB38;
	case 3:
		goto loc_9224DB38;
	case 4:
		goto loc_9224DB38;
	case 5:
		goto loc_9224DF10;
	case 6:
		goto loc_9224D6AC;
	case 7:
		goto loc_9224DF10;
	case 8:
		goto loc_9224DF10;
	case 9:
		goto loc_9224DF10;
	case 10:
		goto loc_9224DF10;
	case 11:
		goto loc_9224DAE4;
	case 12:
		goto loc_9224D80C;
	case 13:
		goto loc_9224D808;
	case 14:
		goto loc_9224DF10;
	case 15:
		goto loc_9224DF10;
	case 16:
		goto loc_9224D38C;
	case 17:
		goto loc_9224DF10;
	case 18:
		goto loc_9224D80C;
	case 19:
		goto loc_9224DF10;
	case 20:
		goto loc_9224DF10;
	case 21:
		goto loc_9224D6B0;
	case 22:
		goto loc_9224DF10;
	case 23:
		goto loc_9224DF10;
	case 24:
		goto loc_9224D39C;
	default:
		__builtin_trap(); // Switch case out of range
	}
loc_9224D37C:
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// bne cr6,0x9224d38c
	if (!ctx.cr6.eq) goto loc_9224D38C;
	// li r17,1
	ctx.r17.s64 = 1;
	// addi r16,r16,1
	ctx.r16.s64 = ctx.r16.s64 + 1;
loc_9224D38C:
	// extsb. r11,r28
	ctx.r11.s64 = ctx.r28.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// ble 0x9224d4dc
	if (!ctx.cr0.gt) goto loc_9224D4DC;
	// li r24,1
	ctx.r24.s64 = 1;
	// b 0x9224d4dc
	goto loc_9224D4DC;
loc_9224D39C:
	// extsb. r11,r28
	ctx.r11.s64 = ctx.r28.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// ble 0x9224d3a8
	if (!ctx.cr0.gt) goto loc_9224D3A8;
	// li r24,1
	ctx.r24.s64 = 1;
loc_9224D3A8:
	// addi r6,r10,1
	ctx.r6.s64 = ctx.r10.s64 + 1;
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// stw r6,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r6.u32);
	// cmplwi cr6,r11,94
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 94, ctx.xer);
	// bne cr6,0x9224d3c4
	if (!ctx.cr6.eq) goto loc_9224D3C4;
	// addi r6,r6,1
	ctx.r6.s64 = ctx.r6.s64 + 1;
	// li r25,-1
	ctx.r25.s64 = -1;
loc_9224D3C4:
	// addi r11,r1,144
	ctx.r11.s64 = ctx.r1.s64 + 144;
	// li r5,0
	ctx.r5.s64 = 0;
	// cmpwi cr6,r19,123
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 123, ctx.xer);
	// std r5,0(r11)
	REX_STORE_U64(ctx.r11.u32 + 0, ctx.r5.u64);
	// std r5,8(r11)
	REX_STORE_U64(ctx.r11.u32 + 8, ctx.r5.u64);
	// std r5,16(r11)
	REX_STORE_U64(ctx.r11.u32 + 16, ctx.r5.u64);
	// std r5,24(r11)
	REX_STORE_U64(ctx.r11.u32 + 24, ctx.r5.u64);
	// bne cr6,0x9224d400
	if (!ctx.cr6.eq) goto loc_9224D400;
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// cmplwi cr6,r11,93
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 93, ctx.xer);
	// bne cr6,0x9224d400
	if (!ctx.cr6.eq) goto loc_9224D400;
	// li r11,32
	ctx.r11.s64 = 32;
	// li r27,93
	ctx.r27.s64 = 93;
	// addi r6,r6,1
	ctx.r6.s64 = ctx.r6.s64 + 1;
	// stb r11,155(r1)
	REX_STORE_U8(ctx.r1.u32 + 155, ctx.r11.u8);
loc_9224D400:
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// cmplwi cr6,r11,93
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 93, ctx.xer);
	// beq cr6,0x9224d4c4
	if (ctx.cr6.eq) goto loc_9224D4C4;
	// li r4,1
	ctx.r4.s64 = 1;
loc_9224D410:
	// mr r8,r11
	ctx.r8.u64 = ctx.r11.u64;
	// addi r6,r6,1
	ctx.r6.s64 = ctx.r6.s64 + 1;
	// clrlwi r9,r8,24
	ctx.r9.u64 = ctx.r8.u32 & 0xFF;
	// cmplwi cr6,r9,45
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 45, ctx.xer);
	// bne cr6,0x9224d498
	if (!ctx.cr6.eq) goto loc_9224D498;
	// clrlwi. r10,r27,24
	ctx.r10.u64 = ctx.r27.u32 & 0xFF;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// beq 0x9224d498
	if (ctx.cr0.eq) goto loc_9224D498;
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// cmplwi cr6,r11,93
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 93, ctx.xer);
	// beq cr6,0x9224d498
	if (ctx.cr6.eq) goto loc_9224D498;
	// clrlwi r9,r11,24
	ctx.r9.u64 = ctx.r11.u32 & 0xFF;
	// addi r6,r6,1
	ctx.r6.s64 = ctx.r6.s64 + 1;
	// cmplw cr6,r10,r9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, ctx.r9.u32, ctx.xer);
	// bge cr6,0x9224d450
	if (!ctx.cr6.lt) goto loc_9224D450;
	// mr r10,r11
	ctx.r10.u64 = ctx.r11.u64;
	// b 0x9224d458
	goto loc_9224D458;
loc_9224D450:
	// mr r10,r27
	ctx.r10.u64 = ctx.r27.u64;
	// mr r27,r11
	ctx.r27.u64 = ctx.r11.u64;
loc_9224D458:
	// clrlwi r7,r10,24
	ctx.r7.u64 = ctx.r10.u32 & 0xFF;
	// clrlwi r11,r27,24
	ctx.r11.u64 = ctx.r27.u32 & 0xFF;
	// b 0x9224d488
	goto loc_9224D488;
loc_9224D464:
	// rlwinm r10,r11,29,3,31
	ctx.r10.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 29) & 0x1FFFFFFF;
	// addi r8,r11,1
	ctx.r8.s64 = ctx.r11.s64 + 1;
	// clrlwi r11,r11,29
	ctx.r11.u64 = ctx.r11.u32 & 0x7;
	// addi r9,r1,144
	ctx.r9.s64 = ctx.r1.s64 + 144;
	// slw r3,r4,r11
	ctx.r3.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r4.u32 << (ctx.r11.u8 & 0x3F));
	// clrlwi r11,r8,24
	ctx.r11.u64 = ctx.r8.u32 & 0xFF;
	// lbzx r8,r10,r9
	ctx.r8.u64 = REX_LOAD_U8(ctx.r10.u32 + ctx.r9.u32);
	// or r8,r3,r8
	ctx.r8.u64 = ctx.r3.u64 | ctx.r8.u64;
	// stbx r8,r10,r9
	REX_STORE_U8(ctx.r10.u32 + ctx.r9.u32, ctx.r8.u8);
loc_9224D488:
	// cmplw cr6,r11,r7
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, ctx.r7.u32, ctx.xer);
	// ble cr6,0x9224d464
	if (!ctx.cr6.gt) goto loc_9224D464;
	// mr r27,r5
	ctx.r27.u64 = ctx.r5.u64;
	// b 0x9224d4b8
	goto loc_9224D4B8;
loc_9224D498:
	// rlwinm r11,r9,29,3,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 29) & 0x1FFFFFFF;
	// clrlwi r9,r9,29
	ctx.r9.u64 = ctx.r9.u32 & 0x7;
	// addi r10,r1,144
	ctx.r10.s64 = ctx.r1.s64 + 144;
	// mr r27,r8
	ctx.r27.u64 = ctx.r8.u64;
	// lbzx r8,r11,r10
	ctx.r8.u64 = REX_LOAD_U8(ctx.r11.u32 + ctx.r10.u32);
	// slw r9,r4,r9
	ctx.r9.u64 = ctx.r9.u8 & 0x20 ? 0 : (ctx.r4.u32 << (ctx.r9.u8 & 0x3F));
	// or r9,r9,r8
	ctx.r9.u64 = ctx.r9.u64 | ctx.r8.u64;
	// stbx r9,r11,r10
	REX_STORE_U8(ctx.r11.u32 + ctx.r10.u32, ctx.r9.u8);
loc_9224D4B8:
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// cmplwi cr6,r11,93
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 93, ctx.xer);
	// bne cr6,0x9224d410
	if (!ctx.cr6.eq) goto loc_9224D410;
loc_9224D4C4:
	// lbz r11,0(r6)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r6.u32 + 0);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// cmpwi cr6,r19,123
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 123, ctx.xer);
	// bne cr6,0x9224d4dc
	if (!ctx.cr6.eq) goto loc_9224D4DC;
	// stw r6,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r6.u32);
loc_9224D4DC:
	// lwz r30,88(r1)
	ctx.r30.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// mr r31,r30
	ctx.r31.u64 = ctx.r30.u64;
	// beq cr6,0x9224d4fc
	if (ctx.cr6.eq) goto loc_9224D4FC;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224D4FC;
	sub_921F5E20(ctx, base);
loc_9224D4FC:
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d510
	if (ctx.cr6.eq) goto loc_9224D510;
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// addi r16,r16,-1
	ctx.r16.s64 = ctx.r16.s64 + -1;
	// beq cr6,0x9224d660
	if (ctx.cr6.eq) goto loc_9224D660;
loc_9224D510:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d538
	if (ctx.cr0.lt) goto loc_9224D538;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d544
	goto loc_9224D544;
loc_9224D538:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D540;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D544:
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224d648
	if (ctx.cr6.eq) goto loc_9224D648;
	// cmpwi cr6,r19,99
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 99, ctx.xer);
	// beq cr6,0x9224d5a8
	if (ctx.cr6.eq) goto loc_9224D5A8;
	// cmpwi cr6,r19,115
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 115, ctx.xer);
	// bne cr6,0x9224d574
	if (!ctx.cr6.eq) goto loc_9224D574;
	// cmpwi cr6,r23,9
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 9, ctx.xer);
	// blt cr6,0x9224d56c
	if (ctx.cr6.lt) goto loc_9224D56C;
	// cmpwi cr6,r23,13
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 13, ctx.xer);
	// ble cr6,0x9224d648
	if (!ctx.cr6.gt) goto loc_9224D648;
loc_9224D56C:
	// cmpwi cr6,r23,32
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 32, ctx.xer);
	// bne cr6,0x9224d5a8
	if (!ctx.cr6.eq) goto loc_9224D5A8;
loc_9224D574:
	// cmpwi cr6,r19,123
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 123, ctx.xer);
	// bne cr6,0x9224d648
	if (!ctx.cr6.eq) goto loc_9224D648;
	// srawi r9,r23,3
	ctx.xer.ca = (ctx.r23.s32 < 0) & ((ctx.r23.u32 & 0x7) != 0);
	ctx.r9.s64 = ctx.r23.s32 >> 3;
	// addi r10,r1,144
	ctx.r10.s64 = ctx.r1.s64 + 144;
	// clrlwi r11,r23,29
	ctx.r11.u64 = ctx.r23.u32 & 0x7;
	// extsb r8,r25
	ctx.r8.s64 = ctx.r25.s8;
	// lbzx r10,r9,r10
	ctx.r10.u64 = REX_LOAD_U8(ctx.r9.u32 + ctx.r10.u32);
	// li r9,1
	ctx.r9.s64 = 1;
	// extsb r10,r10
	ctx.r10.s64 = ctx.r10.s8;
	// xor r10,r10,r8
	ctx.r10.u64 = ctx.r10.u64 ^ ctx.r8.u64;
	// slw r11,r9,r11
	ctx.r11.u64 = ctx.r11.u8 & 0x20 ? 0 : (ctx.r9.u32 << (ctx.r11.u8 & 0x3F));
	// and. r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 & ctx.r10.u64;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224d648
	if (ctx.cr0.eq) goto loc_9224D648;
loc_9224D5A8:
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224d640
	if (!ctx.cr6.eq) goto loc_9224D640;
	// extsb. r11,r24
	ctx.r11.s64 = ctx.r24.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224d630
	if (ctx.cr0.eq) goto loc_9224D630;
	// extsb r11,r23
	ctx.r11.s64 = ctx.r23.s8;
	// clrlwi r3,r11,24
	ctx.r3.u64 = ctx.r11.u32 & 0xFF;
	// stb r11,112(r1)
	REX_STORE_U8(ctx.r1.u32 + 112, ctx.r11.u8);
	// bl 0x92064658
	ctx.lr = 0x9224D5CC;
	sub_92064658(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224d608
	if (ctx.cr0.eq) goto loc_9224D608;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d5fc
	if (ctx.cr0.lt) goto loc_9224D5FC;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r3,0(r11)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d604
	goto loc_9224D604;
loc_9224D5FC:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D604;
	sub_9205FF58(ctx, base);
loc_9224D604:
	// stb r3,113(r1)
	REX_STORE_U8(ctx.r1.u32 + 113, ctx.r3.u8);
loc_9224D608:
	// li r11,63
	ctx.r11.s64 = 63;
	// li r5,1
	ctx.r5.s64 = 1;
	// addi r4,r1,112
	ctx.r4.s64 = ctx.r1.s64 + 112;
	// addi r3,r1,96
	ctx.r3.s64 = ctx.r1.s64 + 96;
	// sth r11,96(r1)
	REX_STORE_U16(ctx.r1.u32 + 96, ctx.r11.u16);
	// bl 0x92064680
	ctx.lr = 0x9224D620;
	sub_92064680(ctx, base);
	// lhz r11,96(r1)
	ctx.r11.u64 = REX_LOAD_U16(ctx.r1.u32 + 96);
	// sth r11,0(r30)
	REX_STORE_U16(ctx.r30.u32 + 0, ctx.r11.u16);
	// addi r30,r30,2
	ctx.r30.s64 = ctx.r30.s64 + 2;
	// b 0x9224d638
	goto loc_9224D638;
loc_9224D630:
	// stb r23,0(r30)
	REX_STORE_U8(ctx.r30.u32 + 0, ctx.r23.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
loc_9224D638:
	// stw r30,88(r1)
	REX_STORE_U32(ctx.r1.u32 + 88, ctx.r30.u32);
	// b 0x9224d4fc
	goto loc_9224D4FC;
loc_9224D640:
	// addi r31,r31,1
	ctx.r31.s64 = ctx.r31.s64 + 1;
	// b 0x9224d4fc
	goto loc_9224D4FC;
loc_9224D648:
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224d660
	if (ctx.cr6.eq) goto loc_9224D660;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224D660;
	sub_921F5E20(ctx, base);
loc_9224D660:
	// cmplw cr6,r31,r30
	ctx.cr6.compare<uint32_t>(ctx.r31.u32, ctx.r30.u32, ctx.xer);
	// beq cr6,0x9224e058
	if (ctx.cr6.eq) goto loc_9224E058;
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224df3c
	if (!ctx.cr6.eq) goto loc_9224DF3C;
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// cmpwi cr6,r19,99
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 99, ctx.xer);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// beq cr6,0x9224df3c
	if (ctx.cr6.eq) goto loc_9224DF3C;
	// lwz r10,88(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// extsb. r11,r24
	ctx.r11.s64 = ctx.r24.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224d6a0
	if (ctx.cr0.eq) goto loc_9224D6A0;
	// li r11,0
	ctx.r11.s64 = 0;
	// sth r11,0(r10)
	REX_STORE_U16(ctx.r10.u32 + 0, ctx.r11.u16);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224D6A0:
	// li r11,0
	ctx.r11.s64 = 0;
	// stb r11,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r11.u8);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224D6AC:
	// li r19,100
	ctx.r19.s64 = 100;
loc_9224D6B0:
	// cmpwi cr6,r23,45
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 45, ctx.xer);
	// bne cr6,0x9224d6c0
	if (!ctx.cr6.eq) goto loc_9224D6C0;
	// li r20,1
	ctx.r20.s64 = 1;
	// b 0x9224d6c8
	goto loc_9224D6C8;
loc_9224D6C0:
	// cmpwi cr6,r23,43
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 43, ctx.xer);
	// bne cr6,0x9224d714
	if (!ctx.cr6.eq) goto loc_9224D714;
loc_9224D6C8:
	// addic. r16,r16,-1
	ctx.xer.ca = ctx.r16.u32 > 0;
	ctx.r16.s64 = ctx.r16.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// bne 0x9224d6e0
	if (!ctx.cr0.eq) goto loc_9224D6E0;
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d6e0
	if (ctx.cr6.eq) goto loc_9224D6E0;
	// li r29,1
	ctx.r29.s64 = 1;
	// b 0x9224d714
	goto loc_9224D714;
loc_9224D6E0:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d708
	if (ctx.cr0.lt) goto loc_9224D708;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d714
	goto loc_9224D714;
loc_9224D708:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D710;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D714:
	// cmpwi cr6,r23,48
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 48, ctx.xer);
	// bne cr6,0x9224d870
	if (!ctx.cr6.eq) goto loc_9224D870;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d744
	if (ctx.cr0.lt) goto loc_9224D744;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d750
	goto loc_9224D750;
loc_9224D744:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D74C;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D750:
	// extsb r11,r23
	ctx.r11.s64 = ctx.r23.s8;
	// cmpwi cr6,r11,120
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 120, ctx.xer);
	// beq cr6,0x9224d7b0
	if (ctx.cr6.eq) goto loc_9224D7B0;
	// cmpwi cr6,r11,88
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 88, ctx.xer);
	// beq cr6,0x9224d7b0
	if (ctx.cr6.eq) goto loc_9224D7B0;
	// li r18,1
	ctx.r18.s64 = 1;
	// cmpwi cr6,r19,120
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 120, ctx.xer);
	// beq cr6,0x9224d790
	if (ctx.cr6.eq) goto loc_9224D790;
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d788
	if (ctx.cr6.eq) goto loc_9224D788;
	// addic. r16,r16,-1
	ctx.xer.ca = ctx.r16.u32 > 0;
	ctx.r16.s64 = ctx.r16.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// bne 0x9224d788
	if (!ctx.cr0.eq) goto loc_9224D788;
	// addi r11,r29,1
	ctx.r11.s64 = ctx.r29.s64 + 1;
	// extsb r29,r11
	ctx.r29.s64 = ctx.r11.s8;
loc_9224D788:
	// li r19,111
	ctx.r19.s64 = 111;
	// b 0x9224d870
	goto loc_9224D870;
loc_9224D790:
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224d7a8
	if (ctx.cr6.eq) goto loc_9224D7A8;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224D7A8;
	sub_921F5E20(ctx, base);
loc_9224D7A8:
	// li r23,48
	ctx.r23.s64 = 48;
	// b 0x9224d870
	goto loc_9224D870;
loc_9224D7B0:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d7d8
	if (ctx.cr0.lt) goto loc_9224D7D8;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d7e4
	goto loc_9224D7E4;
loc_9224D7D8:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D7E0;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D7E4:
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d800
	if (ctx.cr6.eq) goto loc_9224D800;
	// addi r16,r16,-2
	ctx.r16.s64 = ctx.r16.s64 + -2;
	// cmpwi cr6,r16,1
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 1, ctx.xer);
	// bge cr6,0x9224d800
	if (!ctx.cr6.lt) goto loc_9224D800;
	// addi r11,r29,1
	ctx.r11.s64 = ctx.r29.s64 + 1;
	// extsb r29,r11
	ctx.r29.s64 = ctx.r11.s8;
loc_9224D800:
	// li r19,120
	ctx.r19.s64 = 120;
	// b 0x9224d870
	goto loc_9224D870;
loc_9224D808:
	// li r15,1
	ctx.r15.s64 = 1;
loc_9224D80C:
	// cmpwi cr6,r23,45
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 45, ctx.xer);
	// bne cr6,0x9224d81c
	if (!ctx.cr6.eq) goto loc_9224D81C;
	// li r20,1
	ctx.r20.s64 = 1;
	// b 0x9224d824
	goto loc_9224D824;
loc_9224D81C:
	// cmpwi cr6,r23,43
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 43, ctx.xer);
	// bne cr6,0x9224d870
	if (!ctx.cr6.eq) goto loc_9224D870;
loc_9224D824:
	// addic. r16,r16,-1
	ctx.xer.ca = ctx.r16.u32 > 0;
	ctx.r16.s64 = ctx.r16.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// bne 0x9224d83c
	if (!ctx.cr0.eq) goto loc_9224D83C;
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224d83c
	if (ctx.cr6.eq) goto loc_9224D83C;
	// li r29,1
	ctx.r29.s64 = 1;
	// b 0x9224d870
	goto loc_9224D870;
loc_9224D83C:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d864
	if (ctx.cr0.lt) goto loc_9224D864;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d870
	goto loc_9224D870;
loc_9224D864:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D86C;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224D870:
	// cmpwi cr6,r21,0
	ctx.cr6.compare<int32_t>(ctx.r21.s32, 0, ctx.xer);
	// extsb. r30,r29
	ctx.r30.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// beq cr6,0x9224d9a4
	if (ctx.cr6.eq) goto loc_9224D9A4;
	// bne 0x9224d98c
	if (!ctx.cr0.eq) goto loc_9224D98C;
	// ld r28,120(r1)
	ctx.r28.u64 = REX_LOAD_U64(ctx.r1.u32 + 120);
loc_9224D884:
	// cmpwi cr6,r19,120
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 120, ctx.xer);
	// beq cr6,0x9224d8c4
	if (ctx.cr6.eq) goto loc_9224D8C4;
	// cmpwi cr6,r19,112
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 112, ctx.xer);
	// beq cr6,0x9224d8c4
	if (ctx.cr6.eq) goto loc_9224D8C4;
	// clrlwi r3,r23,24
	ctx.r3.u64 = ctx.r23.u32 & 0xFF;
	// bl 0x92063678
	ctx.lr = 0x9224D89C;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224d8f8
	if (ctx.cr0.eq) goto loc_9224D8F8;
	// cmpwi cr6,r19,111
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 111, ctx.xer);
	// bne cr6,0x9224d8bc
	if (!ctx.cr6.eq) goto loc_9224D8BC;
	// cmpwi cr6,r23,56
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 56, ctx.xer);
	// bge cr6,0x9224d8f8
	if (!ctx.cr6.lt) goto loc_9224D8F8;
	// rldicr r28,r28,3,60
	ctx.r28.u64 = __builtin_rotateleft64(ctx.r28.u64, 3) & 0xFFFFFFFFFFFFFFF8;
	// b 0x9224d900
	goto loc_9224D900;
loc_9224D8BC:
	// mulli r28,r28,10
	ctx.r28.s64 = static_cast<int64_t>(ctx.r28.u64 * static_cast<uint64_t>(10));
	// b 0x9224d900
	goto loc_9224D900;
loc_9224D8C4:
	// clrlwi r31,r23,24
	ctx.r31.u64 = ctx.r23.u32 & 0xFF;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063698
	ctx.lr = 0x9224D8D0;
	sub_92063698(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224d8f8
	if (ctx.cr0.eq) goto loc_9224D8F8;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// rldicr r28,r28,4,59
	ctx.r28.u64 = __builtin_rotateleft64(ctx.r28.u64, 4) & 0xFFFFFFFFFFFFFFF0;
	// bl 0x92063678
	ctx.lr = 0x9224D8E4;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224d900
	if (!ctx.cr0.eq) goto loc_9224D900;
	// rlwinm r11,r23,0,27,25
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r23.u32 | (ctx.r23.u64 << 32), 0) & 0xFFFFFFFFFFFFFFDF;
	// addi r23,r11,-7
	ctx.r23.s64 = ctx.r11.s64 + -7;
	// b 0x9224d900
	goto loc_9224D900;
loc_9224D8F8:
	// addi r11,r30,1
	ctx.r11.s64 = ctx.r30.s64 + 1;
	// extsb r29,r11
	ctx.r29.s64 = ctx.r11.s8;
loc_9224D900:
	// extsb. r11,r29
	ctx.r11.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224d968
	if (!ctx.cr0.eq) goto loc_9224D968;
	// addi r11,r23,-48
	ctx.r11.s64 = ctx.r23.s64 + -48;
	// addi r18,r18,1
	ctx.r18.s64 = ctx.r18.s64 + 1;
	// extsw r11,r11
	ctx.r11.s64 = ctx.r11.s32;
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// add r28,r11,r28
	ctx.r28.u64 = ctx.r11.u64 + ctx.r28.u64;
	// beq cr6,0x9224d930
	if (ctx.cr6.eq) goto loc_9224D930;
	// addic. r16,r16,-1
	ctx.xer.ca = ctx.r16.u32 > 0;
	ctx.r16.s64 = ctx.r16.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// bne 0x9224d930
	if (!ctx.cr0.eq) goto loc_9224D930;
	// li r29,1
	ctx.r29.s64 = 1;
	// b 0x9224d980
	goto loc_9224D980;
loc_9224D930:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224d958
	if (ctx.cr0.lt) goto loc_9224D958;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224d980
	goto loc_9224D980;
loc_9224D958:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224D960;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
	// b 0x9224d980
	goto loc_9224D980;
loc_9224D968:
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224d980
	if (ctx.cr6.eq) goto loc_9224D980;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224D980;
	sub_921F5E20(ctx, base);
loc_9224D980:
	// extsb. r30,r29
	ctx.r30.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// beq 0x9224d884
	if (ctx.cr0.eq) goto loc_9224D884;
	// std r28,120(r1)
	REX_STORE_U64(ctx.r1.u32 + 120, ctx.r28.u64);
loc_9224D98C:
	// extsb. r11,r20
	ctx.r11.s64 = ctx.r20.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224dab4
	if (ctx.cr0.eq) goto loc_9224DAB4;
	// ld r11,120(r1)
	ctx.r11.u64 = REX_LOAD_U64(ctx.r1.u32 + 120);
	// neg r11,r11
	ctx.r11.s64 = static_cast<int64_t>(-ctx.r11.u64);
	// std r11,120(r1)
	REX_STORE_U64(ctx.r1.u32 + 120, ctx.r11.u64);
	// b 0x9224dab4
	goto loc_9224DAB4;
loc_9224D9A4:
	// bne 0x9224daa8
	if (!ctx.cr0.eq) goto loc_9224DAA8;
loc_9224D9A8:
	// cmpwi cr6,r19,120
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 120, ctx.xer);
	// beq cr6,0x9224d9e8
	if (ctx.cr6.eq) goto loc_9224D9E8;
	// cmpwi cr6,r19,112
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 112, ctx.xer);
	// beq cr6,0x9224d9e8
	if (ctx.cr6.eq) goto loc_9224D9E8;
	// clrlwi r3,r23,24
	ctx.r3.u64 = ctx.r23.u32 & 0xFF;
	// bl 0x92063678
	ctx.lr = 0x9224D9C0;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224da1c
	if (ctx.cr0.eq) goto loc_9224DA1C;
	// cmpwi cr6,r19,111
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 111, ctx.xer);
	// bne cr6,0x9224d9e0
	if (!ctx.cr6.eq) goto loc_9224D9E0;
	// cmpwi cr6,r23,56
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 56, ctx.xer);
	// bge cr6,0x9224da1c
	if (!ctx.cr6.lt) goto loc_9224DA1C;
	// rlwinm r22,r22,3,0,28
	ctx.r22.u64 = __builtin_rotateleft64(ctx.r22.u32 | (ctx.r22.u64 << 32), 3) & 0xFFFFFFF8;
	// b 0x9224da24
	goto loc_9224DA24;
loc_9224D9E0:
	// mulli r22,r22,10
	ctx.r22.s64 = static_cast<int64_t>(ctx.r22.u64 * static_cast<uint64_t>(10));
	// b 0x9224da24
	goto loc_9224DA24;
loc_9224D9E8:
	// clrlwi r31,r23,24
	ctx.r31.u64 = ctx.r23.u32 & 0xFF;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063698
	ctx.lr = 0x9224D9F4;
	sub_92063698(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224da1c
	if (ctx.cr0.eq) goto loc_9224DA1C;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// rlwinm r22,r22,4,0,27
	ctx.r22.u64 = __builtin_rotateleft64(ctx.r22.u32 | (ctx.r22.u64 << 32), 4) & 0xFFFFFFF0;
	// bl 0x92063678
	ctx.lr = 0x9224DA08;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224da24
	if (!ctx.cr0.eq) goto loc_9224DA24;
	// rlwinm r11,r23,0,27,25
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r23.u32 | (ctx.r23.u64 << 32), 0) & 0xFFFFFFFFFFFFFFDF;
	// addi r23,r11,-7
	ctx.r23.s64 = ctx.r11.s64 + -7;
	// b 0x9224da24
	goto loc_9224DA24;
loc_9224DA1C:
	// addi r11,r30,1
	ctx.r11.s64 = ctx.r30.s64 + 1;
	// extsb r29,r11
	ctx.r29.s64 = ctx.r11.s8;
loc_9224DA24:
	// extsb. r11,r29
	ctx.r11.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne 0x9224da88
	if (!ctx.cr0.eq) goto loc_9224DA88;
	// add r11,r22,r23
	ctx.r11.u64 = ctx.r22.u64 + ctx.r23.u64;
	// addi r18,r18,1
	ctx.r18.s64 = ctx.r18.s64 + 1;
	// addi r22,r11,-48
	ctx.r22.s64 = ctx.r11.s64 + -48;
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// beq cr6,0x9224da50
	if (ctx.cr6.eq) goto loc_9224DA50;
	// addic. r16,r16,-1
	ctx.xer.ca = ctx.r16.u32 > 0;
	ctx.r16.s64 = ctx.r16.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// bne 0x9224da50
	if (!ctx.cr0.eq) goto loc_9224DA50;
	// li r29,1
	ctx.r29.s64 = 1;
	// b 0x9224daa0
	goto loc_9224DAA0;
loc_9224DA50:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224da78
	if (ctx.cr0.lt) goto loc_9224DA78;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224daa0
	goto loc_9224DAA0;
loc_9224DA78:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DA80;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
	// b 0x9224daa0
	goto loc_9224DAA0;
loc_9224DA88:
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224daa0
	if (ctx.cr6.eq) goto loc_9224DAA0;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224DAA0;
	sub_921F5E20(ctx, base);
loc_9224DAA0:
	// extsb. r30,r29
	ctx.r30.s64 = ctx.r29.s8;
	ctx.cr0.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// beq 0x9224d9a8
	if (ctx.cr0.eq) goto loc_9224D9A8;
loc_9224DAA8:
	// extsb. r11,r20
	ctx.r11.s64 = ctx.r20.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224dab4
	if (ctx.cr0.eq) goto loc_9224DAB4;
	// neg r22,r22
	ctx.r22.s64 = static_cast<int64_t>(-ctx.r22.u64);
loc_9224DAB4:
	// cmpwi cr6,r19,70
	ctx.cr6.compare<int32_t>(ctx.r19.s32, 70, ctx.xer);
	// bne cr6,0x9224dac0
	if (!ctx.cr6.eq) goto loc_9224DAC0;
	// li r18,0
	ctx.r18.s64 = 0;
loc_9224DAC0:
	// cmpwi cr6,r18,0
	ctx.cr6.compare<int32_t>(ctx.r18.s32, 0, ctx.xer);
	// beq cr6,0x9224e058
	if (ctx.cr6.eq) goto loc_9224E058;
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224df3c
	if (!ctx.cr6.eq) goto loc_9224DF3C;
	// lwz r11,92(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r11.u32);
	// b 0x9224db00
	goto loc_9224DB00;
loc_9224DAE4:
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// mr r22,r14
	ctx.r22.u64 = ctx.r14.u64;
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224df3c
	if (!ctx.cr6.eq) goto loc_9224DF3C;
	// bl 0x92064638
	ctx.lr = 0x9224DAF8;
	sub_92064638(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224df3c
	if (ctx.cr0.eq) goto loc_9224DF3C;
loc_9224DB00:
	// cmpwi cr6,r21,0
	ctx.cr6.compare<int32_t>(ctx.r21.s32, 0, ctx.xer);
	// beq cr6,0x9224db18
	if (ctx.cr6.eq) goto loc_9224DB18;
	// ld r11,120(r1)
	ctx.r11.u64 = REX_LOAD_U64(ctx.r1.u32 + 120);
	// lwz r10,88(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// std r11,0(r10)
	REX_STORE_U64(ctx.r10.u32 + 0, ctx.r11.u64);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224DB18:
	// extsb. r11,r15
	ctx.r11.s64 = ctx.r15.s8;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224db2c
	if (ctx.cr0.eq) goto loc_9224DB2C;
	// lwz r11,88(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// stw r22,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r22.u32);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224DB2C:
	// lwz r10,88(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// sth r22,0(r10)
	REX_STORE_U16(ctx.r10.u32 + 0, ctx.r22.u16);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224DB38:
	// li r30,0
	ctx.r30.s64 = 0;
	// cmpwi cr6,r23,45
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 45, ctx.xer);
	// bne cr6,0x9224db58
	if (!ctx.cr6.eq) goto loc_9224DB58;
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// li r11,45
	ctx.r11.s64 = 45;
	// li r30,1
	ctx.r30.s64 = 1;
	// stb r11,0(r10)
	REX_STORE_U8(ctx.r10.u32 + 0, ctx.r11.u8);
	// b 0x9224db60
	goto loc_9224DB60;
loc_9224DB58:
	// cmpwi cr6,r23,43
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 43, ctx.xer);
	// bne cr6,0x9224db98
	if (!ctx.cr6.eq) goto loc_9224DB98;
loc_9224DB60:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r16,r16,-1
	ctx.r16.s64 = ctx.r16.s64 + -1;
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224db8c
	if (ctx.cr0.lt) goto loc_9224DB8C;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224db98
	goto loc_9224DB98;
loc_9224DB8C:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DB94;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DB98:
	// cmpwi cr6,r17,0
	ctx.cr6.compare<int32_t>(ctx.r17.s32, 0, ctx.xer);
	// bne cr6,0x9224dc18
	if (!ctx.cr6.eq) goto loc_9224DC18;
	// li r16,-1
	ctx.r16.s64 = -1;
	// b 0x9224dc18
	goto loc_9224DC18;
loc_9224DBA8:
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// addi r16,r16,-1
	ctx.r16.s64 = ctx.r16.s64 + -1;
	// beq cr6,0x9224dc2c
	if (ctx.cr6.eq) goto loc_9224DC2C;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// addi r18,r18,1
	ctx.r18.s64 = ctx.r18.s64 + 1;
	// stbx r31,r30,r11
	REX_STORE_U8(ctx.r30.u32 + ctx.r11.u32, ctx.r31.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DBDC;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224dc0c
	if (ctx.cr0.lt) goto loc_9224DC0C;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224dc18
	goto loc_9224DC18;
loc_9224DC0C:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DC14;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DC18:
	// clrlwi r31,r23,24
	ctx.r31.u64 = ctx.r23.u32 & 0xFF;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063678
	ctx.lr = 0x9224DC24;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224dba8
	if (!ctx.cr0.eq) goto loc_9224DBA8;
loc_9224DC2C:
	// lwz r11,128(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// extsb r10,r23
	ctx.r10.s64 = ctx.r23.s8;
	// lwz r11,0(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// lwz r11,188(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 188);
	// lwz r11,0(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// lbz r31,0(r11)
	ctx.r31.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// extsb r11,r31
	ctx.r11.s64 = ctx.r31.s8;
	// cmpw cr6,r11,r10
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r10.s32, ctx.xer);
	// bne cr6,0x9224dd44
	if (!ctx.cr6.eq) goto loc_9224DD44;
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// addi r16,r16,-1
	ctx.r16.s64 = ctx.r16.s64 + -1;
	// beq cr6,0x9224dd44
	if (ctx.cr6.eq) goto loc_9224DD44;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224dc84
	if (ctx.cr0.lt) goto loc_9224DC84;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224dc90
	goto loc_9224DC90;
loc_9224DC84:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DC8C;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DC90:
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// stbx r31,r30,r11
	REX_STORE_U8(ctx.r30.u32 + ctx.r11.u32, ctx.r31.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DCB4;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// b 0x9224dd30
	goto loc_9224DD30;
loc_9224DCC0:
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// addi r16,r16,-1
	ctx.r16.s64 = ctx.r16.s64 + -1;
	// beq cr6,0x9224dd44
	if (ctx.cr6.eq) goto loc_9224DD44;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// addi r18,r18,1
	ctx.r18.s64 = ctx.r18.s64 + 1;
	// stbx r31,r30,r11
	REX_STORE_U8(ctx.r30.u32 + ctx.r11.u32, ctx.r31.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DCF4;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224dd24
	if (ctx.cr0.lt) goto loc_9224DD24;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224dd30
	goto loc_9224DD30;
loc_9224DD24:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DD2C;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DD30:
	// clrlwi r31,r23,24
	ctx.r31.u64 = ctx.r23.u32 & 0xFF;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063678
	ctx.lr = 0x9224DD3C;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224dcc0
	if (!ctx.cr0.eq) goto loc_9224DCC0;
loc_9224DD44:
	// cmpwi cr6,r18,0
	ctx.cr6.compare<int32_t>(ctx.r18.s32, 0, ctx.xer);
	// beq cr6,0x9224dea8
	if (ctx.cr6.eq) goto loc_9224DEA8;
	// cmpwi cr6,r23,101
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 101, ctx.xer);
	// beq cr6,0x9224dd5c
	if (ctx.cr6.eq) goto loc_9224DD5C;
	// cmpwi cr6,r23,69
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 69, ctx.xer);
	// bne cr6,0x9224dea8
	if (!ctx.cr6.eq) goto loc_9224DEA8;
loc_9224DD5C:
	// cmpwi cr6,r16,0
	ctx.cr6.compare<int32_t>(ctx.r16.s32, 0, ctx.xer);
	// addi r29,r16,-1
	ctx.r29.s64 = ctx.r16.s64 + -1;
	// beq cr6,0x9224dea8
	if (ctx.cr6.eq) goto loc_9224DEA8;
	// lwz r10,84(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// li r11,101
	ctx.r11.s64 = 101;
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// stbx r11,r30,r10
	REX_STORE_U8(ctx.r30.u32 + ctx.r10.u32, ctx.r11.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DD90;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224ddc0
	if (ctx.cr0.lt) goto loc_9224DDC0;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224ddcc
	goto loc_9224DDCC;
loc_9224DDC0:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DDC8;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DDCC:
	// cmpwi cr6,r23,45
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 45, ctx.xer);
	// bne cr6,0x9224de08
	if (!ctx.cr6.eq) goto loc_9224DE08;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// li r10,45
	ctx.r10.s64 = 45;
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// stbx r10,r30,r11
	REX_STORE_U8(ctx.r30.u32 + ctx.r11.u32, ctx.r10.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DDFC;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
	// b 0x9224de10
	goto loc_9224DE10;
loc_9224DE08:
	// cmpwi cr6,r23,43
	ctx.cr6.compare<int32_t>(ctx.r23.s32, 43, ctx.xer);
	// bne cr6,0x9224de94
	if (!ctx.cr6.eq) goto loc_9224DE94;
loc_9224DE10:
	// cmpwi cr6,r29,0
	ctx.cr6.compare<int32_t>(ctx.r29.s32, 0, ctx.xer);
	// addi r29,r29,-1
	ctx.r29.s64 = ctx.r29.s64 + -1;
	// bne cr6,0x9224de60
	if (!ctx.cr6.eq) goto loc_9224DE60;
	// li r29,0
	ctx.r29.s64 = 0;
	// b 0x9224de94
	goto loc_9224DE94;
loc_9224DE24:
	// cmpwi cr6,r29,0
	ctx.cr6.compare<int32_t>(ctx.r29.s32, 0, ctx.xer);
	// addi r29,r29,-1
	ctx.r29.s64 = ctx.r29.s64 + -1;
	// beq cr6,0x9224dea8
	if (ctx.cr6.eq) goto loc_9224DEA8;
	// lwz r11,84(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r7,r1,100
	ctx.r7.s64 = ctx.r1.s64 + 100;
	// addi r6,r1,176
	ctx.r6.s64 = ctx.r1.s64 + 176;
	// addi r5,r1,84
	ctx.r5.s64 = ctx.r1.s64 + 84;
	// addi r4,r1,104
	ctx.r4.s64 = ctx.r1.s64 + 104;
	// addi r18,r18,1
	ctx.r18.s64 = ctx.r18.s64 + 1;
	// stbx r31,r30,r11
	REX_STORE_U8(ctx.r30.u32 + ctx.r11.u32, ctx.r31.u8);
	// addi r30,r30,1
	ctx.r30.s64 = ctx.r30.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x9224ce00
	ctx.lr = 0x9224DE58;
	sub_9224CE00(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e058
	if (ctx.cr0.eq) goto loc_9224E058;
loc_9224DE60:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224de88
	if (ctx.cr0.lt) goto loc_9224DE88;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224de94
	goto loc_9224DE94;
loc_9224DE88:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DE90;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DE94:
	// clrlwi r31,r23,24
	ctx.r31.u64 = ctx.r23.u32 & 0xFF;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063678
	ctx.lr = 0x9224DEA0;
	sub_92063678(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne 0x9224de24
	if (!ctx.cr0.eq) goto loc_9224DE24;
loc_9224DEA8:
	// addi r14,r14,-1
	ctx.r14.s64 = ctx.r14.s64 + -1;
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224dec0
	if (ctx.cr6.eq) goto loc_9224DEC0;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224DEC0;
	sub_921F5E20(ctx, base);
loc_9224DEC0:
	// cmpwi cr6,r18,0
	ctx.cr6.compare<int32_t>(ctx.r18.s32, 0, ctx.xer);
	// beq cr6,0x9224e058
	if (ctx.cr6.eq) goto loc_9224E058;
	// lwz r11,108(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224df3c
	if (!ctx.cr6.eq) goto loc_9224DF3C;
	// lwz r10,92(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// extsb r11,r15
	ctx.r11.s64 = ctx.r15.s8;
	// lwz r5,84(r1)
	ctx.r5.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// lwz r6,128(r1)
	ctx.r6.u64 = REX_LOAD_U32(ctx.r1.u32 + 128);
	// lwz r4,88(r1)
	ctx.r4.u64 = REX_LOAD_U32(ctx.r1.u32 + 88);
	// addi r3,r11,-1
	ctx.r3.s64 = ctx.r11.s64 + -1;
	// stw r10,92(r1)
	REX_STORE_U32(ctx.r1.u32 + 92, ctx.r10.u32);
	// li r10,0
	ctx.r10.s64 = 0;
	// stbx r10,r30,r5
	REX_STORE_U8(ctx.r30.u32 + ctx.r5.u32, ctx.r10.u8);
	// lwz r10,132(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 132);
	// lwz r10,28(r10)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r10.u32 + 28);
	// mtctr r10
	ctx.ctr.u64 = ctx.r10.u64;
	// bctrl 
	ctx.lr = 0x9224DF0C;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
	// b 0x9224df3c
	goto loc_9224DF3C;
loc_9224DF10:
	// lbz r11,0(r10)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r10.u32 + 0);
	// cmpw cr6,r11,r23
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r23.s32, ctx.xer);
	// bne cr6,0x9224e044
	if (!ctx.cr6.eq) goto loc_9224E044;
	// lbz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r1.u32 + 80);
	// lwz r10,108(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 108);
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// cmpwi cr6,r10,0
	ctx.cr6.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// stb r11,80(r1)
	REX_STORE_U8(ctx.r1.u32 + 80, ctx.r11.u8);
	// bne cr6,0x9224df3c
	if (!ctx.cr6.eq) goto loc_9224DF3C;
	// lwz r11,136(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 136);
	// stw r11,732(r1)
	REX_STORE_U32(ctx.r1.u32 + 732, ctx.r11.u32);
loc_9224DF3C:
	// lbz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r1.u32 + 80);
	// lwz r10,716(r1)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// addi r10,r10,1
	ctx.r10.s64 = ctx.r10.s64 + 1;
	// rotlwi r19,r10,0
	ctx.r19.u64 = __builtin_rotateleft32(ctx.r10.u32, 0);
	// stb r11,80(r1)
	REX_STORE_U8(ctx.r1.u32 + 80, ctx.r11.u8);
	// stw r10,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r10.u32);
	// b 0x9224dffc
	goto loc_9224DFFC;
loc_9224DF5C:
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r14,r14,1
	ctx.r14.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224df84
	if (ctx.cr0.lt) goto loc_9224DF84;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r23,0(r11)
	ctx.r23.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224df90
	goto loc_9224DF90;
loc_9224DF84:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DF8C;
	sub_9205FF58(ctx, base);
	// mr r23,r3
	ctx.r23.u64 = ctx.r3.u64;
loc_9224DF90:
	// lbz r11,0(r19)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// addi r19,r19,1
	ctx.r19.s64 = ctx.r19.s64 + 1;
	// cmpw cr6,r11,r23
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r23.s32, ctx.xer);
	// stw r19,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r19.u32);
	// bne cr6,0x9224e044
	if (!ctx.cr6.eq) goto loc_9224E044;
	// clrlwi r3,r23,24
	ctx.r3.u64 = ctx.r23.u32 & 0xFF;
	// bl 0x92064658
	ctx.lr = 0x9224DFAC;
	sub_92064658(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224dffc
	if (ctx.cr0.eq) goto loc_9224DFFC;
	// lwz r11,4(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 4);
	// addi r31,r14,1
	ctx.r31.s64 = ctx.r14.s64 + 1;
	// addic. r11,r11,-1
	ctx.xer.ca = ctx.r11.u32 > 0;
	ctx.r11.s64 = ctx.r11.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// stw r11,4(r26)
	REX_STORE_U32(ctx.r26.u32 + 4, ctx.r11.u32);
	// blt 0x9224dfdc
	if (ctx.cr0.lt) goto loc_9224DFDC;
	// lwz r11,0(r26)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r26.u32 + 0);
	// addi r10,r11,1
	ctx.r10.s64 = ctx.r11.s64 + 1;
	// lbz r3,0(r11)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stw r10,0(r26)
	REX_STORE_U32(ctx.r26.u32 + 0, ctx.r10.u32);
	// b 0x9224dfe4
	goto loc_9224DFE4;
loc_9224DFDC:
	// mr r3,r26
	ctx.r3.u64 = ctx.r26.u64;
	// bl 0x9205ff58
	ctx.lr = 0x9224DFE4;
	sub_9205FF58(ctx, base);
loc_9224DFE4:
	// lbz r11,0(r19)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// addi r19,r19,1
	ctx.r19.s64 = ctx.r19.s64 + 1;
	// cmpw cr6,r11,r3
	ctx.cr6.compare<int32_t>(ctx.r11.s32, ctx.r3.s32, ctx.xer);
	// stw r19,716(r1)
	REX_STORE_U32(ctx.r1.u32 + 716, ctx.r19.u32);
	// bne cr6,0x9224e034
	if (!ctx.cr6.eq) goto loc_9224E034;
	// addi r14,r31,-1
	ctx.r14.s64 = ctx.r31.s64 + -1;
loc_9224DFFC:
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// bne cr6,0x9224e024
	if (!ctx.cr6.eq) goto loc_9224E024;
	// lbz r11,0(r19)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// cmplwi cr6,r11,37
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 37, ctx.xer);
	// bne cr6,0x9224e058
	if (!ctx.cr6.eq) goto loc_9224E058;
	// lwz r11,716(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
	// lbz r11,1(r11)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r11.u32 + 1);
	// cmplwi cr6,r11,110
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 110, ctx.xer);
	// bne cr6,0x9224e058
	if (!ctx.cr6.eq) goto loc_9224E058;
	// lwz r19,716(r1)
	ctx.r19.u64 = REX_LOAD_U32(ctx.r1.u32 + 716);
loc_9224E024:
	// lbz r3,0(r19)
	ctx.r3.u64 = REX_LOAD_U8(ctx.r19.u32 + 0);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne 0x9224d020
	if (!ctx.cr0.eq) goto loc_9224D020;
	// b 0x9224e058
	goto loc_9224E058;
loc_9224E034:
	// cmpwi cr6,r3,-1
	ctx.cr6.compare<int32_t>(ctx.r3.s32, -1, ctx.xer);
	// beq cr6,0x9224e044
	if (ctx.cr6.eq) goto loc_9224E044;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224E044;
	sub_921F5E20(ctx, base);
loc_9224E044:
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// beq cr6,0x9224e058
	if (ctx.cr6.eq) goto loc_9224E058;
	// mr r4,r26
	ctx.r4.u64 = ctx.r26.u64;
	// mr r3,r23
	ctx.r3.u64 = ctx.r23.u64;
	// bl 0x921f5e20
	ctx.lr = 0x9224E058;
	sub_921F5E20(ctx, base);
loc_9224E058:
	// lwz r11,100(r1)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r1.u32 + 100);
	// cmpwi cr6,r11,1
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 1, ctx.xer);
	// bne cr6,0x9224e06c
	if (!ctx.cr6.eq) goto loc_9224E06C;
	// lwz r3,84(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 84);
	// bl 0x9205f5c8
	ctx.lr = 0x9224E06C;
	sub_9205F5C8(ctx, base);
loc_9224E06C:
	// cmpwi cr6,r23,-1
	ctx.cr6.compare<int32_t>(ctx.r23.s32, -1, ctx.xer);
	// bne cr6,0x9224e090
	if (!ctx.cr6.eq) goto loc_9224E090;
	// lwz r3,92(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
	// cmpwi cr6,r3,0
	ctx.cr6.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// bne cr6,0x9224e094
	if (!ctx.cr6.eq) goto loc_9224E094;
	// lbz r11,80(r1)
	ctx.r11.u64 = REX_LOAD_U8(ctx.r1.u32 + 80);
	// cmplwi r11,0
	ctx.cr0.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// bne 0x9224e094
	if (!ctx.cr0.eq) goto loc_9224E094;
	// b 0x9224cf00
	goto loc_9224CF00;
loc_9224E090:
	// lwz r3,92(r1)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r1.u32 + 92);
loc_9224E094:
	// addi r1,r1,688
	ctx.r1.s64 = ctx.r1.s64 + 688;
	// b 0x9205b490
	__restgprlr_14(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E0A0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r10,r4
	ctx.r10.u64 = ctx.r4.u64;
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq cr6,0x9224e0c4
	if (ctx.cr6.eq) goto loc_9224E0C4;
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// bne cr6,0x9224e0f4
	if (!ctx.cr6.eq) goto loc_9224E0F4;
loc_9224E0C4:
	// bl 0x9205f378
	ctx.lr = 0x9224E0C8;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224E0EC;
	sub_9205F228(ctx, base);
	// li r3,22
	ctx.r3.s64 = 22;
	// b 0x9224e1a0
	goto loc_9224E1A0;
loc_9224E0F4:
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x9224e108
	if (!ctx.cr6.eq) goto loc_9224E108;
	// li r11,0
	ctx.r11.s64 = 0;
	// stb r11,0(r3)
	REX_STORE_U8(ctx.r3.u32 + 0, ctx.r11.u8);
	// b 0x9224e0c4
	goto loc_9224E0C4;
loc_9224E108:
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
loc_9224E10C:
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// cmplwi cr6,r9,0
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
	// beq cr6,0x9224e124
	if (ctx.cr6.eq) goto loc_9224E124;
	// addic. r10,r10,-1
	ctx.xer.ca = ctx.r10.u32 > 0;
	ctx.r10.s64 = ctx.r10.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// bne 0x9224e10c
	if (!ctx.cr0.eq) goto loc_9224E10C;
loc_9224E124:
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// bne cr6,0x9224e160
	if (!ctx.cr6.eq) goto loc_9224E160;
	// li r11,0
	ctx.r11.s64 = 0;
	// stb r11,0(r3)
	REX_STORE_U8(ctx.r3.u32 + 0, ctx.r11.u8);
	// bl 0x9205f378
	ctx.lr = 0x9224E138;
	sub_9205F378(ctx, base);
	// li r31,22
	ctx.r31.s64 = 22;
loc_9224E13C:
	// stw r31,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r31.u32);
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f228
	ctx.lr = 0x9224E158;
	sub_9205F228(ctx, base);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// b 0x9224e1a0
	goto loc_9224E1A0;
loc_9224E160:
	// lbz r9,0(r5)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r5.u32 + 0);
	// addi r5,r5,1
	ctx.r5.s64 = ctx.r5.s64 + 1;
	// cmplwi r9,0
	ctx.cr0.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
	// stb r9,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r9.u8);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// beq 0x9224e180
	if (ctx.cr0.eq) goto loc_9224E180;
	// addic. r10,r10,-1
	ctx.xer.ca = ctx.r10.u32 > 0;
	ctx.r10.s64 = ctx.r10.s64 + -1;
	ctx.cr0.compare<int32_t>(ctx.r10.s32, 0, ctx.xer);
	// bne 0x9224e160
	if (!ctx.cr0.eq) goto loc_9224E160;
loc_9224E180:
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// bne cr6,0x9224e19c
	if (!ctx.cr6.eq) goto loc_9224E19C;
	// li r11,0
	ctx.r11.s64 = 0;
	// stb r11,0(r3)
	REX_STORE_U8(ctx.r3.u32 + 0, ctx.r11.u8);
	// bl 0x9205f378
	ctx.lr = 0x9224E194;
	sub_9205F378(ctx, base);
	// li r31,34
	ctx.r31.s64 = 34;
	// b 0x9224e13c
	goto loc_9224E13C;
loc_9224E19C:
	// li r3,0
	ctx.r3.s64 = 0;
loc_9224E1A0:
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E1B8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// cmplwi cr6,r4,0
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, 0, ctx.xer);
	// bne cr6,0x9224e200
	if (!ctx.cr6.eq) goto loc_9224E200;
	// bl 0x9205f378
	ctx.lr = 0x9224E1D4;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224E1F8;
	sub_9205F228(ctx, base);
	// li r3,22
	ctx.r3.s64 = 22;
	// b 0x9224e320
	goto loc_9224E320;
loc_9224E200:
	// cmplwi cr6,r5,0
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, 0, ctx.xer);
	// bne cr6,0x9224e234
	if (!ctx.cr6.eq) goto loc_9224E234;
loc_9224E208:
	// bl 0x9205f378
	ctx.lr = 0x9224E20C;
	sub_9205F378(ctx, base);
	// li r31,22
	ctx.r31.s64 = 22;
	// stw r31,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r31.u32);
loc_9224E214:
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f228
	ctx.lr = 0x9224E22C;
	sub_9205F228(ctx, base);
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// b 0x9224e320
	goto loc_9224E320;
loc_9224E234:
	// cntlzw r11,r7
	ctx.r11.u64 = ctx.r7.u32 == 0 ? 32 : __builtin_clz(ctx.r7.u32);
	// li r31,0
	ctx.r31.s64 = 0;
	// rlwinm r11,r11,27,31,31
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 27) & 0x1;
	// xori r11,r11,1
	ctx.r11.u64 = ctx.r11.u64 ^ 1;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stb r31,0(r4)
	REX_STORE_U8(ctx.r4.u32 + 0, ctx.r31.u8);
	// cmplw cr6,r5,r11
	ctx.cr6.compare<uint32_t>(ctx.r5.u32, ctx.r11.u32, ctx.xer);
	// bgt cr6,0x9224e268
	if (ctx.cr6.gt) goto loc_9224E268;
loc_9224E254:
	// bl 0x9205f378
	ctx.lr = 0x9224E258;
	sub_9205F378(ctx, base);
	// li r11,34
	ctx.r11.s64 = 34;
	// mr r31,r11
	ctx.r31.u64 = ctx.r11.u64;
	// stw r11,0(r3)
	REX_STORE_U32(ctx.r3.u32 + 0, ctx.r11.u32);
	// b 0x9224e214
	goto loc_9224E214;
loc_9224E268:
	// addi r11,r6,-2
	ctx.r11.s64 = ctx.r6.s64 + -2;
	// cmplwi cr6,r11,34
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 34, ctx.xer);
	// bgt cr6,0x9224e208
	if (ctx.cr6.gt) goto loc_9224E208;
	// mr r9,r31
	ctx.r9.u64 = ctx.r31.u64;
	// mr r11,r4
	ctx.r11.u64 = ctx.r4.u64;
	// cmpwi cr6,r7,0
	ctx.cr6.compare<int32_t>(ctx.r7.s32, 0, ctx.xer);
	// beq cr6,0x9224e298
	if (ctx.cr6.eq) goto loc_9224E298;
	// li r10,45
	ctx.r10.s64 = 45;
	// addi r11,r4,1
	ctx.r11.s64 = ctx.r4.s64 + 1;
	// li r9,1
	ctx.r9.s64 = 1;
	// neg r3,r3
	ctx.r3.s64 = static_cast<int64_t>(-ctx.r3.u64);
	// stb r10,0(r4)
	REX_STORE_U8(ctx.r4.u32 + 0, ctx.r10.u8);
loc_9224E298:
	// mr r8,r11
	ctx.r8.u64 = ctx.r11.u64;
loc_9224E29C:
	// divwu r10,r3,r6
	ctx.r10.u64 = uint32_t(ctx.r6.u32 ? ctx.r3.u32 / ctx.r6.u32 : 0);
	// twllei r6,0
	if (ctx.r6.s32 == 0 || ctx.r6.u32 < 0u) ppc_trap(ctx, base, 0);
	// mullw r10,r10,r6
	ctx.r10.s64 = int64_t(ctx.r10.s32) * int64_t(ctx.r6.s32);
	// subf r10,r10,r3
	ctx.r10.u64 = ctx.r3.u64 - ctx.r10.u64;
	// divwu r3,r3,r6
	ctx.r3.u64 = uint32_t(ctx.r6.u32 ? ctx.r3.u32 / ctx.r6.u32 : 0);
	// twllei r6,0
	if (ctx.r6.s32 == 0 || ctx.r6.u32 < 0u) ppc_trap(ctx, base, 0);
	// cmplwi cr6,r10,9
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 9, ctx.xer);
	// ble cr6,0x9224e2c4
	if (!ctx.cr6.gt) goto loc_9224E2C4;
	// addi r10,r10,87
	ctx.r10.s64 = ctx.r10.s64 + 87;
	// b 0x9224e2c8
	goto loc_9224E2C8;
loc_9224E2C4:
	// addi r10,r10,48
	ctx.r10.s64 = ctx.r10.s64 + 48;
loc_9224E2C8:
	// stb r10,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r10.u8);
	// addi r9,r9,1
	ctx.r9.s64 = ctx.r9.s64 + 1;
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq cr6,0x9224e2e4
	if (ctx.cr6.eq) goto loc_9224E2E4;
	// cmplw cr6,r9,r5
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r5.u32, ctx.xer);
	// blt cr6,0x9224e29c
	if (ctx.cr6.lt) goto loc_9224E29C;
loc_9224E2E4:
	// cmplw cr6,r9,r5
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, ctx.r5.u32, ctx.xer);
	// blt cr6,0x9224e2f4
	if (ctx.cr6.lt) goto loc_9224E2F4;
	// stb r31,0(r4)
	REX_STORE_U8(ctx.r4.u32 + 0, ctx.r31.u8);
	// b 0x9224e254
	goto loc_9224E254;
loc_9224E2F4:
	// stb r31,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r31.u8);
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
loc_9224E2FC:
	// lbz r9,0(r8)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r8.u32 + 0);
	// lbz r10,0(r11)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// stb r9,0(r11)
	REX_STORE_U8(ctx.r11.u32 + 0, ctx.r9.u8);
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// stb r10,0(r8)
	REX_STORE_U8(ctx.r8.u32 + 0, ctx.r10.u8);
	// addi r8,r8,1
	ctx.r8.s64 = ctx.r8.s64 + 1;
	// cmplw cr6,r8,r11
	ctx.cr6.compare<uint32_t>(ctx.r8.u32, ctx.r11.u32, ctx.xer);
	// blt cr6,0x9224e2fc
	if (ctx.cr6.lt) goto loc_9224E2FC;
	// li r3,0
	ctx.r3.s64 = 0;
loc_9224E320:
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E338) {
	REX_FUNC_PROLOGUE();
	// li r7,0
	ctx.r7.s64 = 0;
	// b 0x9224e1b8
	sub_9224E1B8(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E340) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// li r7,0
	ctx.r7.s64 = 0;
	// addi r11,r11,2408
	ctx.r11.s64 = ctx.r11.s64 + 2408;
	// lwz r8,4(r11)
	ctx.r8.u64 = REX_LOAD_U32(ctx.r11.u32 + 4);
	// lwz r11,8(r8)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r8.u32 + 8);
	// cmpwi cr6,r11,0
	ctx.cr6.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// bne cr6,0x9224e370
	if (!ctx.cr6.eq) goto loc_9224E370;
	// bl 0x920635f0
	ctx.lr = 0x9224E36C;
	sub_920635F0(ctx, base);
	// b 0x9224e410
	goto loc_9224E410;
loc_9224E370:
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// bne cr6,0x9224e3a8
	if (!ctx.cr6.eq) goto loc_9224E3A8;
	// bl 0x9205f378
	ctx.lr = 0x9224E37C;
	sub_9205F378(ctx, base);
	// mr r11,r3
	ctx.r11.u64 = ctx.r3.u64;
	// li r10,22
	ctx.r10.s64 = 22;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// bl 0x9205f228
	ctx.lr = 0x9224E3A0;
	sub_9205F228(ctx, base);
	// li r3,0
	ctx.r3.s64 = 0;
	// b 0x9224e410
	goto loc_9224E410;
loc_9224E3A8:
	// lbz r10,0(r3)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r3.u32 + 0);
	// mr r11,r10
	ctx.r11.u64 = ctx.r10.u64;
	// clrlwi r9,r11,24
	ctx.r9.u64 = ctx.r11.u32 & 0xFF;
	// add r9,r9,r8
	ctx.r9.u64 = ctx.r9.u64 + ctx.r8.u64;
	// lbz r9,29(r9)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r9.u32 + 29);
	// rlwinm. r9,r9,0,29,29
	ctx.r9.u64 = __builtin_rotateleft64(ctx.r9.u32 | (ctx.r9.u64 << 32), 0) & 0x4;
	ctx.cr0.compare<int32_t>(ctx.r9.s32, 0, ctx.xer);
	// beq 0x9224e3f4
	if (ctx.cr0.eq) goto loc_9224E3F4;
	// addi r3,r3,1
	ctx.r3.s64 = ctx.r3.s64 + 1;
	// lbz r10,0(r3)
	ctx.r10.u64 = REX_LOAD_U8(ctx.r3.u32 + 0);
	// cmplwi r10,0
	ctx.cr0.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// beq 0x9224e3ec
	if (ctx.cr0.eq) goto loc_9224E3EC;
	// rlwinm r11,r11,8,0,23
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r11.u32 | (ctx.r11.u64 << 32), 8) & 0xFFFFFF00;
	// or r11,r11,r10
	ctx.r11.u64 = ctx.r11.u64 | ctx.r10.u64;
	// cmplw cr6,r4,r11
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, ctx.r11.u32, ctx.xer);
	// bne cr6,0x9224e400
	if (!ctx.cr6.eq) goto loc_9224E400;
	// addi r7,r3,-1
	ctx.r7.s64 = ctx.r3.s64 + -1;
	// b 0x9224e400
	goto loc_9224E400;
loc_9224E3EC:
	// cmplwi cr6,r7,0
	ctx.cr6.compare<uint32_t>(ctx.r7.u32, 0, ctx.xer);
	// b 0x9224e3f8
	goto loc_9224E3F8;
loc_9224E3F4:
	// cmplw cr6,r4,r11
	ctx.cr6.compare<uint32_t>(ctx.r4.u32, ctx.r11.u32, ctx.xer);
loc_9224E3F8:
	// bne cr6,0x9224e400
	if (!ctx.cr6.eq) goto loc_9224E400;
	// mr r7,r3
	ctx.r7.u64 = ctx.r3.u64;
loc_9224E400:
	// cmplwi cr6,r10,0
	ctx.cr6.compare<uint32_t>(ctx.r10.u32, 0, ctx.xer);
	// addi r3,r3,1
	ctx.r3.s64 = ctx.r3.s64 + 1;
	// bne cr6,0x9224e3a8
	if (!ctx.cr6.eq) goto loc_9224E3A8;
	// mr r3,r7
	ctx.r3.u64 = ctx.r7.u64;
loc_9224E410:
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E420) {
	REX_FUNC_PROLOGUE();
	// li r5,0
	ctx.r5.s64 = 0;
	// b 0x9224e340
	sub_9224E340(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E430) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b478
	ctx.lr = 0x9224E438;
	__savegprlr_28(ctx, base);
	// addi r31,r1,-128
	ctx.r31.s64 = ctx.r1.s64 + -128;
	// stwu r1,-128(r1)
	ea = -128 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// li r3,1
	ctx.r3.s64 = 1;
	// li r28,0
	ctx.r28.s64 = 0;
	// stw r28,84(r31)
	REX_STORE_U32(ctx.r31.u32 + 84, ctx.r28.u32);
	// bl 0x92063450
	ctx.lr = 0x9224E450;
	sub_92063450(ctx, base);
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r30,r11,17568
	ctx.r30.s64 = ctx.r11.s64 + 17568;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r10,r11,17572
	ctx.r10.s64 = ctx.r11.s64 + 17572;
loc_9224E464:
	// stw r28,80(r31)
	REX_STORE_U32(ctx.r31.u32 + 80, ctx.r28.u32);
	// lwz r11,0(r10)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r10.u32 + 0);
	// cmpw cr6,r28,r11
	ctx.cr6.compare<int32_t>(ctx.r28.s32, ctx.r11.s32, ctx.xer);
	// bge cr6,0x9224e4f4
	if (!ctx.cr6.lt) goto loc_9224E4F4;
	// rlwinm r29,r28,2,0,29
	ctx.r29.u64 = __builtin_rotateleft64(ctx.r28.u32 | (ctx.r28.u64 << 32), 2) & 0xFFFFFFFC;
	// lwz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwzx r9,r29,r11
	ctx.r9.u64 = REX_LOAD_U32(ctx.r29.u32 + ctx.r11.u32);
	// cmplwi cr6,r9,0
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
	// beq cr6,0x9224e4e8
	if (ctx.cr6.eq) goto loc_9224E4E8;
	// rotlwi r4,r9,0
	ctx.r4.u64 = __builtin_rotateleft32(ctx.r9.u32, 0);
	// lwz r11,12(r4)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r4.u32 + 12);
	// andi. r11,r11,131
	ctx.r11.u64 = ctx.r11.u64 & 131;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// cmpwi r11,0
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224e4e8
	if (ctx.cr0.eq) goto loc_9224E4E8;
	// mr r3,r28
	ctx.r3.u64 = ctx.r28.u64;
	// bl 0x9205fef0
	ctx.lr = 0x9224E4A4;
	sub_9205FEF0(ctx, base);
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// lwz r11,0(r30)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwzx r3,r29,r11
	ctx.r3.u64 = REX_LOAD_U32(ctx.r29.u32 + ctx.r11.u32);
	// lwz r11,12(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 12);
	// andi. r11,r11,131
	ctx.r11.u64 = ctx.r11.u64 & 131;
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// cmpwi r11,0
	ctx.cr0.compare<int32_t>(ctx.r11.s32, 0, ctx.xer);
	// beq 0x9224e4dc
	if (ctx.cr0.eq) goto loc_9224E4DC;
	// lwz r11,28(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 28);
	// cmplwi cr6,r11,0
	ctx.cr6.compare<uint32_t>(ctx.r11.u32, 0, ctx.xer);
	// beq cr6,0x9224e4dc
	if (ctx.cr6.eq) goto loc_9224E4DC;
	// bl 0x9205bb48
	ctx.lr = 0x9224E4D0;
	sub_9205BB48(ctx, base);
	// lwz r11,84(r31)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r31.u32 + 84);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// stw r11,84(r31)
	REX_STORE_U32(ctx.r31.u32 + 84, ctx.r11.u32);
loc_9224E4DC:
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// addi r12,r31,128
	ctx.r12.s64 = ctx.r31.s64 + 128;
	// bl 0x9224e55c
	ctx.lr = 0x9224E4E8;
	sub_9224E55C(ctx, base);
loc_9224E4E8:
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// addi r28,r28,1
	ctx.r28.s64 = ctx.r28.s64 + 1;
	// b 0x9224e464
	goto loc_9224E464;
loc_9224E4F4:
	// mr r8,r8
	ctx.r8.u64 = ctx.r8.u64;
	// addi r12,r31,128
	ctx.r12.s64 = ctx.r31.s64 + 128;
	// bl 0x9224e50c
	ctx.lr = 0x9224E500;
	sub_9224E50C(ctx, base);
	// lwz r3,84(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 84);
	// addi r1,r31,128
	ctx.r1.s64 = ctx.r31.s64 + 128;
	// b 0x9205b4c8
	__restgprlr_28(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E50C) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// li r3,1
	ctx.r3.s64 = 1;
	// bl 0x920632f0
	ctx.lr = 0x9224E520;
	sub_920632F0(ctx, base);
	// lwz r1,0(r1)
	ctx.r1.u64 = REX_LOAD_U32(ctx.r1.u32 + 0);
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E530) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// std r31,-8(r1)
	REX_STORE_U64(ctx.r1.u32 + -8, ctx.r31.u64);
	// addi r31,r12,-128
	ctx.r31.s64 = ctx.r12.s64 + -128;
	// std r30,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r30.u64);
	// std r28,-24(r1)
	REX_STORE_U64(ctx.r1.u32 + -24, ctx.r28.u64);
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-32(r1)
	REX_STORE_U32(ctx.r1.u32 + -32, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r30,r11,17568
	ctx.r30.s64 = ctx.r11.s64 + 17568;
	// lwz r28,80(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// b 0x9224e578
	goto loc_9224E578;
loc_9224E578:
	// rlwinm r11,r28,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r28.u32 | (ctx.r28.u64 << 32), 2) & 0xFFFFFFFC;
	// mr r3,r28
	ctx.r3.u64 = ctx.r28.u64;
	// lwz r10,0(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwzx r4,r11,r10
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r10.u32);
	// bl 0x9205ff40
	ctx.lr = 0x9224E58C;
	sub_9205FF40(ctx, base);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r30,r11,17568
	ctx.r30.s64 = ctx.r11.s64 + 17568;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r10,r11,17572
	ctx.r10.s64 = ctx.r11.s64 + 17572;
	// lwz r28,80(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// lwz r1,0(r1)
	ctx.r1.u64 = REX_LOAD_U32(ctx.r1.u32 + 0);
	// ld r31,-8(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -8);
	// ld r30,-16(r1)
	ctx.r30.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// ld r28,-24(r1)
	ctx.r28.u64 = REX_LOAD_U64(ctx.r1.u32 + -24);
	// lwz r12,-32(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -32);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E55C) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// std r31,-8(r1)
	REX_STORE_U64(ctx.r1.u32 + -8, ctx.r31.u64);
	// addi r31,r12,-128
	ctx.r31.s64 = ctx.r12.s64 + -128;
	// std r30,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r30.u64);
	// std r28,-24(r1)
	REX_STORE_U64(ctx.r1.u32 + -24, ctx.r28.u64);
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-32(r1)
	REX_STORE_U32(ctx.r1.u32 + -32, ctx.r12.u32);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// rlwinm r11,r28,2,0,29
	ctx.r11.u64 = __builtin_rotateleft64(ctx.r28.u32 | (ctx.r28.u64 << 32), 2) & 0xFFFFFFFC;
	// mr r3,r28
	ctx.r3.u64 = ctx.r28.u64;
	// lwz r10,0(r30)
	ctx.r10.u64 = REX_LOAD_U32(ctx.r30.u32 + 0);
	// lwzx r4,r11,r10
	ctx.r4.u64 = REX_LOAD_U32(ctx.r11.u32 + ctx.r10.u32);
	// bl 0x9205ff40
	ctx.lr = 0x9224E58C;
	sub_9205FF40(ctx, base);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r30,r11,17568
	ctx.r30.s64 = ctx.r11.s64 + 17568;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r10,r11,17572
	ctx.r10.s64 = ctx.r11.s64 + 17572;
	// lwz r28,80(r31)
	ctx.r28.u64 = REX_LOAD_U32(ctx.r31.u32 + 80);
	// lwz r1,0(r1)
	ctx.r1.u64 = REX_LOAD_U32(ctx.r1.u32 + 0);
	// ld r31,-8(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -8);
	// ld r30,-16(r1)
	ctx.r30.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// ld r28,-24(r1)
	ctx.r28.u64 = REX_LOAD_U64(ctx.r1.u32 + -24);
	// lwz r12,-32(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -32);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E5C0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// bl 0x9205b47c
	ctx.lr = 0x9224E5C8;
	__savegprlr_29(ctx, base);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// mr r29,r3
	ctx.r29.u64 = ctx.r3.u64;
	// cmplwi cr6,r29,0
	ctx.cr6.compare<uint32_t>(ctx.r29.u32, 0, ctx.xer);
	// beq cr6,0x9224e648
	if (ctx.cr6.eq) goto loc_9224E648;
	// mr r11,r29
	ctx.r11.u64 = ctx.r29.u64;
	// mr r10,r11
	ctx.r10.u64 = ctx.r11.u64;
loc_9224E5E0:
	// lbz r9,0(r11)
	ctx.r9.u64 = REX_LOAD_U8(ctx.r11.u32 + 0);
	// addi r11,r11,1
	ctx.r11.s64 = ctx.r11.s64 + 1;
	// cmplwi cr6,r9,0
	ctx.cr6.compare<uint32_t>(ctx.r9.u32, 0, ctx.xer);
	// bne cr6,0x9224e5e0
	if (!ctx.cr6.eq) goto loc_9224E5E0;
	// subf r11,r10,r11
	ctx.r11.u64 = ctx.r11.u64 - ctx.r10.u64;
	// addi r11,r11,-1
	ctx.r11.s64 = ctx.r11.s64 + -1;
	// rotlwi r11,r11,0
	ctx.r11.u64 = __builtin_rotateleft32(ctx.r11.u32, 0);
	// addi r30,r11,1
	ctx.r30.s64 = ctx.r11.s64 + 1;
	// mr r3,r30
	ctx.r3.u64 = ctx.r30.u64;
	// bl 0x92063130
	ctx.lr = 0x9224E608;
	sub_92063130(ctx, base);
	// mr. r31,r3
	ctx.r31.u64 = ctx.r3.u64;
	ctx.cr0.compare<int32_t>(ctx.r31.s32, 0, ctx.xer);
	// beq 0x9224e648
	if (ctx.cr0.eq) goto loc_9224E648;
	// mr r5,r29
	ctx.r5.u64 = ctx.r29.u64;
	// mr r4,r30
	ctx.r4.u64 = ctx.r30.u64;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x92063860
	ctx.lr = 0x9224E620;
	sub_92063860(ctx, base);
	// cmpwi r3,0
	ctx.cr0.compare<int32_t>(ctx.r3.s32, 0, ctx.xer);
	// beq 0x9224e640
	if (ctx.cr0.eq) goto loc_9224E640;
	// li r7,0
	ctx.r7.s64 = 0;
	// li r6,0
	ctx.r6.s64 = 0;
	// li r5,0
	ctx.r5.s64 = 0;
	// li r4,0
	ctx.r4.s64 = 0;
	// li r3,0
	ctx.r3.s64 = 0;
	// bl 0x9205f290
	ctx.lr = 0x9224E640;
	sub_9205F290(ctx, base);
loc_9224E640:
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// b 0x9224e64c
	goto loc_9224E64C;
loc_9224E648:
	// li r3,0
	ctx.r3.s64 = 0;
loc_9224E64C:
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// b 0x9205b4cc
	__restgprlr_29(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E658) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,-1000
	ctx.r3.s64 = ctx.r11.s64 + -1000;
	// bl 0x92054848
	ctx.lr = 0x9224E670;
	sub_92054848(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5472
	ctx.r3.s64 = ctx.r11.s64 + -5472;
	// bl 0x9205cf90
	ctx.lr = 0x9224E67C;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E690) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,-836
	ctx.r3.s64 = ctx.r11.s64 + -836;
	// bl 0x92054f18
	ctx.lr = 0x9224E6A8;
	sub_92054F18(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5456
	ctx.r3.s64 = ctx.r11.s64 + -5456;
	// bl 0x9205cf90
	ctx.lr = 0x9224E6B4;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E6C8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5440
	ctx.r3.s64 = ctx.r11.s64 + -5440;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E6D8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// li r9,256
	ctx.r9.s64 = 256;
	// addi r10,r11,5248
	ctx.r10.s64 = ctx.r11.s64 + 5248;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r11,r11,360
	ctx.r11.s64 = ctx.r11.s64 + 360;
	// mtctr r9
	ctx.ctr.u64 = ctx.r9.u64;
loc_9224E6F0:
	// stw r10,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r10.u32);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// bdnz 0x9224e6f0
	--ctx.ctr.u64;
	if (ctx.ctr.u32 != 0) goto loc_9224E6F0;
	// lwz r11,0(r10)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r10.u32 + 0);
	// lis r9,-28123
	ctx.r9.s64 = -1843068928;
	// addi r11,r11,256
	ctx.r11.s64 = ctx.r11.s64 + 256;
	// addi r3,r9,-5432
	ctx.r3.s64 = ctx.r9.s64 + -5432;
	// stw r11,0(r10)
	REX_STORE_U32(ctx.r10.u32 + 0, ctx.r11.u32);
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E718) {
	REX_FUNC_PROLOGUE();
	PPCRegister temp{};
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// lfd f1,13928(r11)
	ctx.fpscr.disableFlushMode();
	ctx.f1.u64 = REX_LOAD_U64(ctx.r11.u32 + 13928);
	// bl 0x921f1220
	ctx.lr = 0x9224E730;
	sub_921F1220(ctx, base);
	// lis r11,-28160
	ctx.r11.s64 = -1845493760;
	// frsp f13,f1
	ctx.fpscr.disableFlushMode();
	ctx.f13.f64 = double(float(ctx.f1.f64));
	// lfs f0,16716(r11)
	temp.u32 = REX_LOAD_U32(ctx.r11.u32 + 16716);
	ctx.f0.f64 = double(temp.f32);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// fmuls f0,f13,f0
	ctx.f0.f64 = double(float(ctx.f13.f64 * ctx.f0.f64));
	// stfs f0,7552(r11)
	temp.f32 = float(ctx.f0.f64);
	REX_STORE_U32(ctx.r11.u32 + 7552, temp.u32);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E758) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r4,108
	ctx.r4.s64 = 108;
	// addi r3,r11,10980
	ctx.r3.s64 = ctx.r11.s64 + 10980;
	// b 0x9214c590
	sub_9214C590(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E768) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r4,r11,10980
	ctx.r4.s64 = ctx.r11.s64 + 10980;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11016
	ctx.r3.s64 = ctx.r11.s64 + 11016;
	// b 0x9214aab8
	sub_9214AAB8(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E780) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28122
	ctx.r11.s64 = -1843003392;
	// addi r11,r11,25224
	ctx.r11.s64 = ctx.r11.s64 + 25224;
	// addi r3,r11,4
	ctx.r3.s64 = ctx.r11.s64 + 4;
	// bl 0x9224f05c
	ctx.lr = 0x9224E79C;
	__imp__RtlInitializeCriticalSection(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5344
	ctx.r3.s64 = ctx.r11.s64 + -5344;
	// bl 0x9205cf90
	ctx.lr = 0x9224E7A8;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E7B8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28122
	ctx.r11.s64 = -1843003392;
	// addi r11,r11,25256
	ctx.r11.s64 = ctx.r11.s64 + 25256;
	// addi r3,r11,4
	ctx.r3.s64 = ctx.r11.s64 + 4;
	// bl 0x9224f05c
	ctx.lr = 0x9224E7D4;
	__imp__RtlInitializeCriticalSection(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5320
	ctx.r3.s64 = ctx.r11.s64 + -5320;
	// bl 0x9205cf90
	ctx.lr = 0x9224E7E0;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E7F0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11344
	ctx.r3.s64 = ctx.r11.s64 + 11344;
	// bl 0x921ad1f0
	ctx.lr = 0x9224E808;
	sub_921AD1F0(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5296
	ctx.r3.s64 = ctx.r11.s64 + -5296;
	// bl 0x9205cf90
	ctx.lr = 0x9224E814;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E828) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5280
	ctx.r3.s64 = ctx.r11.s64 + -5280;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E838) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11528
	ctx.r3.s64 = ctx.r11.s64 + 11528;
	// bl 0x921ad1f0
	ctx.lr = 0x9224E850;
	sub_921AD1F0(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5200
	ctx.r3.s64 = ctx.r11.s64 + -5200;
	// bl 0x9205cf90
	ctx.lr = 0x9224E85C;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E870) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5184
	ctx.r3.s64 = ctx.r11.s64 + -5184;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E880) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r9,0
	ctx.r9.s64 = 0;
	// addi r11,r11,11536
	ctx.r11.s64 = ctx.r11.s64 + 11536;
	// li r10,11
	ctx.r10.s64 = 11;
	// mtctr r10
	ctx.ctr.u64 = ctx.r10.u64;
loc_9224E894:
	// stw r9,0(r11)
	REX_STORE_U32(ctx.r11.u32 + 0, ctx.r9.u32);
	// addi r11,r11,4
	ctx.r11.s64 = ctx.r11.s64 + 4;
	// bdnz 0x9224e894
	--ctx.ctr.u64;
	if (ctx.ctr.u32 != 0) goto loc_9224E894;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E8A8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r31,r11,11632
	ctx.r31.s64 = ctx.r11.s64 + 11632;
	// addi r3,r31,156
	ctx.r3.s64 = ctx.r31.s64 + 156;
	// bl 0x921b1268
	ctx.lr = 0x9224E8C8;
	sub_921B1268(ctx, base);
	// li r11,0
	ctx.r11.s64 = 0;
	// li r5,124
	ctx.r5.s64 = 124;
	// li r4,0
	ctx.r4.s64 = 0;
	// addi r3,r31,8
	ctx.r3.s64 = ctx.r31.s64 + 8;
	// stw r11,132(r31)
	REX_STORE_U32(ctx.r31.u32 + 132, ctx.r11.u32);
	// stw r11,0(r31)
	REX_STORE_U32(ctx.r31.u32 + 0, ctx.r11.u32);
	// stw r11,4(r31)
	REX_STORE_U32(ctx.r31.u32 + 4, ctx.r11.u32);
	// stw r11,136(r31)
	REX_STORE_U32(ctx.r31.u32 + 136, ctx.r11.u32);
	// bl 0x9205cd70
	ctx.lr = 0x9224E8EC;
	sub_9205CD70(ctx, base);
	// li r11,0
	ctx.r11.s64 = 0;
	// lis r10,-28123
	ctx.r10.s64 = -1843068928;
	// addi r3,r10,-5168
	ctx.r3.s64 = ctx.r10.s64 + -5168;
	// stw r11,140(r31)
	REX_STORE_U32(ctx.r31.u32 + 140, ctx.r11.u32);
	// stw r11,144(r31)
	REX_STORE_U32(ctx.r31.u32 + 144, ctx.r11.u32);
	// stw r11,148(r31)
	REX_STORE_U32(ctx.r31.u32 + 148, ctx.r11.u32);
	// stw r11,152(r31)
	REX_STORE_U32(ctx.r31.u32 + 152, ctx.r11.u32);
	// bl 0x9205cf90
	ctx.lr = 0x9224E90C;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E920) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11904
	ctx.r3.s64 = ctx.r11.s64 + 11904;
	// bl 0x921ba238
	ctx.lr = 0x9224E938;
	sub_921BA238(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5104
	ctx.r3.s64 = ctx.r11.s64 + -5104;
	// bl 0x9205cf90
	ctx.lr = 0x9224E944;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E958) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r5,100
	ctx.r5.s64 = 100;
	// addi r31,r11,11936
	ctx.r31.s64 = ctx.r11.s64 + 11936;
	// li r4,0
	ctx.r4.s64 = 0;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x9205cd70
	ctx.lr = 0x9224E980;
	sub_9205CD70(ctx, base);
	// li r11,0
	ctx.r11.s64 = 0;
	// li r5,100
	ctx.r5.s64 = 100;
	// li r4,0
	ctx.r4.s64 = 0;
	// addi r3,r31,404
	ctx.r3.s64 = ctx.r31.s64 + 404;
	// stw r11,804(r31)
	REX_STORE_U32(ctx.r31.u32 + 804, ctx.r11.u32);
	// bl 0x9205cd70
	ctx.lr = 0x9224E998;
	sub_9205CD70(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224E9B0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-5088
	ctx.r3.s64 = ctx.r11.s64 + -5088;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E9C0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4696
	ctx.r3.s64 = ctx.r11.s64 + -4696;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224E9D0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r5,108
	ctx.r5.s64 = 108;
	// addi r3,r11,12960
	ctx.r3.s64 = ctx.r11.s64 + 12960;
	// li r4,0
	ctx.r4.s64 = 0;
	// bl 0x9205cd70
	ctx.lr = 0x9224E9F0;
	sub_9205CD70(ctx, base);
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4624
	ctx.r3.s64 = ctx.r11.s64 + -4624;
	// bl 0x9205cf90
	ctx.lr = 0x9224E9FC;
	sub_9205CF90(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EA10) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4608
	ctx.r3.s64 = ctx.r11.s64 + -4608;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EA20) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4496
	ctx.r3.s64 = ctx.r11.s64 + -4496;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EA30) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4480
	ctx.r3.s64 = ctx.r11.s64 + -4480;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EA40) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4512
	ctx.r3.s64 = ctx.r11.s64 + -4512;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EA50) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28123
	ctx.r11.s64 = -1843068928;
	// addi r3,r11,-4416
	ctx.r3.s64 = ctx.r11.s64 + -4416;
	// b 0x9205cf90
	sub_9205CF90(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EA60) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28129
	ctx.r11.s64 = -1843462144;
	// addi r3,r11,30184
	ctx.r3.s64 = ctx.r11.s64 + 30184;
	// bl 0x9205cf90
	ctx.lr = 0x9224EA78;
	sub_9205CF90(ctx, base);
	// lis r11,-28129
	ctx.r11.s64 = -1843462144;
	// addi r3,r11,29992
	ctx.r3.s64 = ctx.r11.s64 + 29992;
	// bl 0x92056ac8
	ctx.lr = 0x9224EA84;
	sub_92056AC8(ctx, base);
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// stw r3,17088(r11)
	REX_STORE_U32(ctx.r11.u32 + 17088, ctx.r3.u32);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EAA0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,-1000
	ctx.r3.s64 = ctx.r11.s64 + -1000;
	// b 0x920544d0
	sub_920544D0(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EAB0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,-836
	ctx.r3.s64 = ctx.r11.s64 + -836;
	// b 0x92054f70
	sub_92054F70(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EAC0) {
	REX_FUNC_PROLOGUE();
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EAC8) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r30,-24(r1)
	REX_STORE_U64(ctx.r1.u32 + -24, ctx.r30.u64);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-112(r1)
	ea = -112 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// li r30,255
	ctx.r30.s64 = 255;
	// addi r11,r11,360
	ctx.r11.s64 = ctx.r11.s64 + 360;
	// addi r31,r11,1024
	ctx.r31.s64 = ctx.r11.s64 + 1024;
loc_9224EAEC:
	// addi r31,r31,-4
	ctx.r31.s64 = ctx.r31.s64 + -4;
	// lwz r3,0(r31)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r31.u32 + 0);
	// bl 0x9206a918
	ctx.lr = 0x9224EAF8;
	sub_9206A918(ctx, base);
	// addi r30,r30,-1
	ctx.r30.s64 = ctx.r30.s64 + -1;
	// cmpwi cr6,r30,0
	ctx.cr6.compare<int32_t>(ctx.r30.s32, 0, ctx.xer);
	// bge cr6,0x9224eaec
	if (!ctx.cr6.lt) goto loc_9224EAEC;
	// addi r1,r1,112
	ctx.r1.s64 = ctx.r1.s64 + 112;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r30,-24(r1)
	ctx.r30.u64 = REX_LOAD_U64(ctx.r1.u32 + -24);
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EB20) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// lis r10,-28122
	ctx.r10.s64 = -1843003392;
	// addi r11,r11,-7168
	ctx.r11.s64 = ctx.r11.s64 + -7168;
	// stw r11,25224(r10)
	REX_STORE_U32(ctx.r10.u32 + 25224, ctx.r11.u32);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EB38) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28157
	ctx.r11.s64 = -1845297152;
	// lis r10,-28122
	ctx.r10.s64 = -1843003392;
	// addi r11,r11,-7168
	ctx.r11.s64 = ctx.r11.s64 + -7168;
	// stw r11,25256(r10)
	REX_STORE_U32(ctx.r10.u32 + 25256, ctx.r11.u32);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EB50) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11344
	ctx.r3.s64 = ctx.r11.s64 + 11344;
	// b 0x921ad260
	sub_921AD260(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EB60) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// lwz r3,11380(r11)
	ctx.r3.u64 = REX_LOAD_U32(ctx.r11.u32 + 11380);
	// cmplwi cr6,r3,0
	ctx.cr6.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq cr6,0x9224eb9c
	if (ctx.cr6.eq) goto loc_9224EB9C;
	// bl 0x9206a050
	ctx.lr = 0x9224EB80;
	sub_9206A050(ctx, base);
	// cmplwi r3,0
	ctx.cr0.compare<uint32_t>(ctx.r3.u32, 0, ctx.xer);
	// beq 0x9224eb9c
	if (ctx.cr0.eq) goto loc_9224EB9C;
	// lwz r11,0(r3)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r3.u32 + 0);
	// li r4,1
	ctx.r4.s64 = 1;
	// lwz r11,0(r11)
	ctx.r11.u64 = REX_LOAD_U32(ctx.r11.u32 + 0);
	// mtctr r11
	ctx.ctr.u64 = ctx.r11.u64;
	// bctrl 
	ctx.lr = 0x9224EB9C;
	REX_CALL_INDIRECT_FUNC(ctx.ctr.u32);
loc_9224EB9C:
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EBB0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11528
	ctx.r3.s64 = ctx.r11.s64 + 11528;
	// b 0x921ad260
	sub_921AD260(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EBC0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11529
	ctx.r3.s64 = ctx.r11.s64 + 11529;
	// b 0x921adcb8
	sub_921ADCB8(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EBD0) {
	REX_FUNC_PROLOGUE();
	uint32_t ea{};
	// mflr r12
	ctx.r12.u64 = ctx.lr;
	// stw r12,-8(r1)
	REX_STORE_U32(ctx.r1.u32 + -8, ctx.r12.u32);
	// std r31,-16(r1)
	REX_STORE_U64(ctx.r1.u32 + -16, ctx.r31.u64);
	// stwu r1,-96(r1)
	ea = -96 + ctx.r1.u32;
	REX_STORE_U32(ea, ctx.r1.u32);
	ctx.r1.u32 = ea;
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r31,r11,11632
	ctx.r31.s64 = ctx.r11.s64 + 11632;
	// mr r3,r31
	ctx.r3.u64 = ctx.r31.u64;
	// bl 0x921b33c0
	ctx.lr = 0x9224EBF0;
	sub_921B33C0(ctx, base);
	// addi r3,r31,156
	ctx.r3.s64 = ctx.r31.s64 + 156;
	// bl 0x921b2d00
	ctx.lr = 0x9224EBF8;
	sub_921B2D00(ctx, base);
	// addi r1,r1,96
	ctx.r1.s64 = ctx.r1.s64 + 96;
	// lwz r12,-8(r1)
	ctx.r12.u64 = REX_LOAD_U32(ctx.r1.u32 + -8);
	// mtlr r12
	ctx.lr = ctx.r12.u64;
	// ld r31,-16(r1)
	ctx.r31.u64 = REX_LOAD_U64(ctx.r1.u32 + -16);
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EC10) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,11904
	ctx.r3.s64 = ctx.r11.s64 + 11904;
	// b 0x921b99d8
	sub_921B99D8(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC20) {
	REX_FUNC_PROLOGUE();
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EC28) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13364
	ctx.r3.s64 = ctx.r11.s64 + 13364;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC38) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13340
	ctx.r3.s64 = ctx.r11.s64 + 13340;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC48) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13316
	ctx.r3.s64 = ctx.r11.s64 + 13316;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC58) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13292
	ctx.r3.s64 = ctx.r11.s64 + 13292;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC68) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13268
	ctx.r3.s64 = ctx.r11.s64 + 13268;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC78) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13412
	ctx.r3.s64 = ctx.r11.s64 + 13412;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC88) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13388
	ctx.r3.s64 = ctx.r11.s64 + 13388;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EC98) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13564
	ctx.r3.s64 = ctx.r11.s64 + 13564;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECA8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13540
	ctx.r3.s64 = ctx.r11.s64 + 13540;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECB8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13860
	ctx.r3.s64 = ctx.r11.s64 + 13860;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECC8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13836
	ctx.r3.s64 = ctx.r11.s64 + 13836;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECD8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13812
	ctx.r3.s64 = ctx.r11.s64 + 13812;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECE8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13788
	ctx.r3.s64 = ctx.r11.s64 + 13788;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ECF8) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13892
	ctx.r3.s64 = ctx.r11.s64 + 13892;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED08) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13940
	ctx.r3.s64 = ctx.r11.s64 + 13940;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED18) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13916
	ctx.r3.s64 = ctx.r11.s64 + 13916;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED28) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13964
	ctx.r3.s64 = ctx.r11.s64 + 13964;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED38) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,13988
	ctx.r3.s64 = ctx.r11.s64 + 13988;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED48) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14064
	ctx.r3.s64 = ctx.r11.s64 + 14064;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED58) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14112
	ctx.r3.s64 = ctx.r11.s64 + 14112;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED68) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14088
	ctx.r3.s64 = ctx.r11.s64 + 14088;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED78) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14136
	ctx.r3.s64 = ctx.r11.s64 + 14136;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED88) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14184
	ctx.r3.s64 = ctx.r11.s64 + 14184;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224ED98) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14160
	ctx.r3.s64 = ctx.r11.s64 + 14160;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EDA8) {
	REX_FUNC_PROLOGUE();
	// blr 
	return;
}

DEFINE_REX_FUNC(sub_9224EDB0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14208
	ctx.r3.s64 = ctx.r11.s64 + 14208;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EDC0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14232
	ctx.r3.s64 = ctx.r11.s64 + 14232;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EDD0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14256
	ctx.r3.s64 = ctx.r11.s64 + 14256;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EDE0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,14280
	ctx.r3.s64 = ctx.r11.s64 + 14280;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EDF0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,12960
	ctx.r3.s64 = ctx.r11.s64 + 12960;
	// b 0x921ca690
	sub_921CA690(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE00) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16460
	ctx.r3.s64 = ctx.r11.s64 + 16460;
	// b 0x921d60b0
	sub_921D60B0(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE10) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16588
	ctx.r3.s64 = ctx.r11.s64 + 16588;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE20) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16612
	ctx.r3.s64 = ctx.r11.s64 + 16612;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE30) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16636
	ctx.r3.s64 = ctx.r11.s64 + 16636;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE40) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16660
	ctx.r3.s64 = ctx.r11.s64 + 16660;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE50) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16684
	ctx.r3.s64 = ctx.r11.s64 + 16684;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE60) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16552
	ctx.r3.s64 = ctx.r11.s64 + 16552;
	// b 0x921d4f38
	sub_921D4F38(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE70) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16520
	ctx.r3.s64 = ctx.r11.s64 + 16520;
	// b 0x921d60b0
	sub_921D60B0(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE80) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16536
	ctx.r3.s64 = ctx.r11.s64 + 16536;
	// b 0x921d60b0
	sub_921D60B0(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EE90) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16716
	ctx.r3.s64 = ctx.r11.s64 + 16716;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EEA0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16740
	ctx.r3.s64 = ctx.r11.s64 + 16740;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EEB0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16764
	ctx.r3.s64 = ctx.r11.s64 + 16764;
	// b 0x921ea280
	sub_921EA280(ctx, base);
	return;
}

DEFINE_REX_FUNC(sub_9224EEC0) {
	REX_FUNC_PROLOGUE();
	// lis r11,-28121
	ctx.r11.s64 = -1842937856;
	// addi r3,r11,16800
	ctx.r3.s64 = ctx.r11.s64 + 16800;
	// b 0x921d8b70
	sub_921D8B70(ctx, base);
	return;
}

