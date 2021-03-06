/*********************************************************************
 *                
 * Copyright (C) 2004-2005,  Karlsruhe University
 *                
 * File path:     arch/ia32/hwcr_k8.h
 * Description:   
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: hwcr_k8.h,v 1.2.2.1 2005/06/24 13:19:13 stoess Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__IA32__HWCR_H__
#define __ARCH__IA32__HWCR_H__

/* HWCR Bits features 26049 p289 */
#define IA32_HWCR_SMMLOCK	( 1 <<  0)        /* SMM lock */			 
#define IA32_HWCR_SLOWFENCE	( 1 <<  1)        /* Slow SFENCE enable */		 
#define IA32_HWCR_TLBCACHEDIS	( 1 <<  3)        /* Cacheable memory disable*/		 
#define IA32_HWCR_INVD_WBINVD	( 1 <<  4)        /* INVD to WBINVD conversion */	 
#define IA32_HWCR_FFDIS		( 1 <<  6)        /* Flush filter disable*/		 
#define IA32_HWCR_DISLOCK	( 1 <<  7)        /* x86 LOCK prefix disable  */	 
#define IA32_HWCR_IGNNE_EM	( 1 <<  8)        /* IGNNE port emulation enable*/	 
#define IA32_HWCR_HLTXSPCYCEN	( 1 << 12)        /* HLT special bus cyle enable  */	 
#define IA32_HWCR_SMISPCYCDIS	( 1 << 13)        /* SMI special bus cyle disable */	 
#define IA32_HWCR_RSMSPCYCDIS	( 1 << 14)        /* RSM special bus cyle disable */	 
#define IA32_HWCR_SSEDIS	( 1 << 15)        /* SSE disable */			 
#define IA32_HWCR_WRAP32DIS	( 1 << 17)        /* 32-bit address wrap disable  */	 
#define IA32_HWCR_MCIS_WREN	( 1 << 18)        /* McI status write enable  */	 
#define IA32_HWCR_START_FID	(63 << 19)        /* startup FID status */               


class ia32_hwcr_t{

public:
    static void dump_hwcr(){
	
	printf("HWCR register:\n");
	
	printf("\tsmmlock: %s\n"
	       "\tslowfence: %s\n"
	       "\ttlbcache: %s\n"
	       "\tinvd_wbinvd: %s\n"
	       "\tflush filter: %s\n"
	       "\tlock prefix: %s\n"
	       "\tignne emulation: %s\n"
	       "\texit from hlt special bus cycle: %s\n" 
	       "\tsmi special bus cycle: %s\n"
	       "\trsm special bus cycle: %s\n"
	       "\tsse: %s\n"
	       "\t32-bit address wrap: %s\n"
	       "\tmci status write: %s\n"
	       "\tstartup fid status: %x\n",
	       (is_smm_locked() ? "enabled" : "disabled" ),
	       (is_slowfence_enabled() ? "enabled" : "disabled" ),
	       (is_ptemem_cached() ? "enabled" : "disabled" ),
	       (is_invd_wbinvd() ? "enabled" : "disabled" ),
	       (is_flushfilter_enabled() ? "enabled" : "disabled" ),
	       (is_lockprefix_enabled() ? "enabled" : "disabled" ),
	       (is_ignne_emulation_enabled() ? "enabled" : "disabled" ),
	       (is_hltx_spc_enabled() ? "enabled" : "disabled" ), 
	       (is_smi_spc_enabled() ? "enabled" : "disabled" ),
	       (is_rsm_spc_enabled() ? "enabled" : "disabled" ),
	       (is_sse_enabled() ? "enabled" : "disabled" ),
	       (is_wrap32_enabled() ? "enabled" : "disabled" ),
	       (is_mci_status_write_enabled() ? "enabled" : "disabled" ),
	       get_startup_fid_status());
    }
    
    static bool is_smm_locked() 
    { 
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_SMMLOCK); 
    }
    static void enable_smmlock() 
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_SMMLOCK);
    }
    static void disable_smmlock()
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_SMMLOCK);
    }

    
    static bool is_slowfence_enabled() 
    { 
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_SLOWFENCE); 
    }	
    static void enable_slowfence()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_SLOWFENCE);
    }

    static void disable_slowfence()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_SMMLOCK);
    }
	
    
    static bool is_ptemem_cached() 
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_TLBCACHEDIS); 
    }	
    static void enable_ptemem_cached()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_TLBCACHEDIS);
    }
    static void disable_ptemem_cached()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_TLBCACHEDIS);
    }
	

    static bool is_invd_wbinvd() { 
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_INVD_WBINVD); 
    }	
    static void enable_invd_wbinvd()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_INVD_WBINVD);
    }
    static void disable_invd_wbinvd()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_INVD_WBINVD);
    }


    static bool is_flushfilter_enabled() 
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_FFDIS); 
    }

    static void enable_flushfilter()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_FFDIS);
    }
    static void disable_flushfilter()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_FFDIS);
    }


    static bool is_lockprefix_enabled() 
    {
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_DISLOCK); 
    }	
    static void enable_lockprefix()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_DISLOCK);
    }
    static void disable_lockprefix()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_DISLOCK);
    }
	

    static bool is_ignne_emulation_enabled() 
    {
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_IGNNE_EM); 
    }	
    static void enable_ignne_emulation()
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_IGNNE_EM);
    }
    static void disable_ignne_emulation()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_IGNNE_EM);
    }

    
    static bool is_hltx_spc_enabled() 
    {
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_HLTXSPCYCEN);
    }	
    static void enable_hltx_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_HLTXSPCYCEN);
    }
    static void disable_hltx_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_HLTXSPCYCEN);
    }


    static bool is_smi_spc_enabled()
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_SMISPCYCDIS); 
    }	
    static void enable_smi_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_SMISPCYCDIS);
    }
    static void disable_smi_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_SMISPCYCDIS);
    }


    static bool is_rsm_spc_enabled() 
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_RSMSPCYCDIS); 
    }	
    static void enable_rsm_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_RSMSPCYCDIS);
    }
    static void disable_rsm_spc()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_RSMSPCYCDIS);
    }


    static bool is_sse_enabled()
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_SSEDIS); 
    }
    static void enable_sse()   
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_SSEDIS);
    }
    static void disable_sse()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_SSEDIS);
    }

    
	
    static bool is_wrap32_enabled() 
    { 
	return !(ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_WRAP32DIS); 
    }	
    static void enable_wrap32()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_WRAP32DIS);
    }

    static void disable_wrap32()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_WRAP32DIS);
    }

    

    static bool is_mci_status_write_enabled() 
    { 
	return (ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_MCIS_WREN); 
    }
    static void enable_mci_status_write()   
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr | IA32_HWCR_MCIS_WREN);
    }
	
    static void disable_mci_status_write()    
    {
	u64_t hwcr = ia32_rdmsr(IA32_HWCR_MSR);
	ia32_wrmsr(IA32_HWCR_MSR, hwcr & ~IA32_HWCR_MCIS_WREN);
    }

    static u8_t get_startup_fid_status()    {
	return (u8_t) ((ia32_rdmsr(IA32_HWCR_MSR) & IA32_HWCR_START_FID) >> 19);
    }
	
};



#endif /* !__ARCH__IA32_HWCR_H__ */
