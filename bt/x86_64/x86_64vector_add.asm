_text SEGMENT

_V4DAddAVX PROC PUBLIC
	vmovupd     ymm0,ymmword ptr [rdx]  
	vmovupd     ymm1,ymmword ptr [rcx]  
	vaddpd      ymm1,ymm0,ymm1  
	vmovupd     ymmword ptr [r8],ymm1
	ret  
_V4DAddAVX ENDP

_V4DSubAVX PROC PUBLIC
	mov rax,r8
	vmovupd     ymm0,ymmword ptr [rdx]  
	vmovupd     ymm1,ymmword ptr [rcx]  
	vsubpd      ymm1,ymm0,ymm1  
	vmovupd     ymmword ptr [rax],ymm1  
	ret  
_V4DSubAVX ENDP

_V4DMulAVX PROC PUBLIC
	mov rax,r8
	vmovupd     ymm0,ymmword ptr [rdx]  
	vmovupd     ymm1,ymmword ptr [rcx]  
	vmulpd      ymm1,ymm0,ymm1  
	vmovupd     ymmword ptr [rax],ymm1  
	ret  
_V4DMulAVX ENDP

_V4DDivAVX PROC PUBLIC
	mov rax,r8
	vmovupd     ymm0,ymmword ptr [rdx]  
	vmovupd     ymm1,ymmword ptr [rcx]  
	vdivpd      ymm1,ymm0,ymm1  
	vmovupd     ymmword ptr [rax],ymm1  
	ret  
_V4DDivAVX ENDP

;_V4DCombineAVX PROC PUBLIC
	;vshufpd     ymm3,ymm3,ymm3,0  
	;mov rax,r8
	vmovupd     ymm0,ymmword ptr [rdx]  
	;vbroadcastsd ymm1,qword ptr [rsp+28h]
	;vshufpd     ymm3,ymm3,ymm3,0  
	;vmulpd      ymm0,ymm1,ymm0  
	;vmovupd     ymm2,ymmword ptr [rcx]  
	;vmulpd      ymm2,ymm2,ymm3  
	;vaddpd      ymm0,ymm2,ymm0  
	;vmovupd     ymmword ptr [rax],ymm0  
	ret
;_V4DCombineAVX ENDP

_text ENDS
END