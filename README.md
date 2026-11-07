# HyperDBG Denial-of-Service

HyperDBG is in beta and its a non-commercial hypervisor; this is just a simple bug I found while developing tooling with it. <br>
Whenever an EPT hook absorbs a page and that page contains _mm_pause it will cause an absurd overhead. A 5 second pause would take hours to complete. <br>
My personal best guess to the cause is likely the VMXRoot [spinlock mechanism](https://docs.hyperdbg.org/design/features/vmm-module/vmx-root-mode-compatible-message-tracing).<br>
That being said I haven't actually checked. It could be an entirely different cause. It works well as an anti tamper tool. <br>
If it is from the spinlock mechanism then it will likely cause the same output on other hypervisors built inspired by the [Hypervisor from scratch"](https://rayanfam.com/topics/hypervisor-from-scratch-part-8/) series (Which is quite a lot of hypervisors). <br>
Still a fun little anti tampering mechanism; against easily the most polished open source hypervisor project. <br>

## Caveats 

It is very important to keep in mind this can't be used as a detection, Only as an anti tamper. The timing system is obviously hookable. Using timing that exposes host time doesn't really work due to the nature of hyperdbg. <br>
I show the unspoofed time in the screenshots. In a real attack basis the timers would be spoofed, they would still spend hours waiting for each hook though. <br>
To be very clear, if you aren't familiar with EPT hooking, you can't just "hook around" the issue due to the fact that you hook the entire physical memory page. <br>
This doesn't affect [breakpoint EPT hooks](https://docs.hyperdbg.org/design/features/vmm-module/design-of-epthook). As they catch the exception rather than stripping MMU page permissions. Exception EPT hooks are fully visible to usermode and break page integrity though.<br> 

## Bare Metal

<img width="454" height="121" alt="image" src="https://github.com/user-attachments/assets/d091aee8-7fcc-4316-8b3a-9c80badd8eba" />


## Hyper DBG

<img width="486" height="115" alt="image" src="https://github.com/user-attachments/assets/cd7e3747-755f-4694-8a5f-411635708506" />
