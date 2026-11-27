# Samsung Galaxy Tab S6 LTE (SM-T865, gts6l) kernel for LineageOS 24.0 — sources and credits

This tree is Linux 4.14 for the Snapdragon 855 Galaxy Tab S6 LTE. It combines the following work;
individual authorship is preserved in the git history wherever the original history was available.

- **Samsung Electronics** — kernel source release for SM-T865 (Linux 4.14.190, GPL-2.0).
- **XiaoYeZi (qaz6750)** — import of the Samsung source and the first fixes
  (github.com/qaz6750/kernel_samsung_sm8150_gts6l); their nine commits are kept as authored,
  re-parented onto upstream v4.14.190.
- **Linux stable (kernel.org)** — 4.14.191 through 4.14.336, merged from the linux-stable tags;
  **OpenELA kernel-lts** — 4.14.336 to 4.14.357 (github.com/openela/kernel-lts). 4.14.357-openela
  (March 2026) is the last 4.14 release of either; later fixes are picked individually.
- **fengkeqei** — conflict resolutions of the Galaxy S10 (SM-G9730) LTS merges
  (github.com/fengkeqei/android_kernel_samsung_sm8150), reused for files whose pre-merge state was
  identical; the merge commits name the S10 commits whose resolutions were used.
- **LineageOS android_kernel_oneplus_sm8150** (lineage-23.2) — the BPF/networking backport series
  maintained there (committed largely by **basamaryan**, with picks by Nick Reuter, Sebastiano
  Barezzi, Michael Bestas, Łukasz Patron, Nolen Johnson and YueNan Zhao; original upstream authors
  kept per commit; in this branch from "msm: sde: restructure trace calls to align with bpf_probe"
  to "UPSTREAM: ANDROID: bpf: do not fail to load if log is full"), the EROFS 5.10 sync (Gao Xiang and others, see the import
  commit), the binder freeze support (BINDER_FREEZE / BINDER_GET_FROZEN_INFO, Marco Ballesio and
  others) that lets Android's app freezer work, the LZ4 updates, and the smp_cond_load_relaxed / xa_lock / attach_page_private backports.
- **LineageOS samsung sm8250 kernels** — the approach for driving the UDFPS finger mask from the
  pressed FOD layer, ported here to Samsung's existing HBM path.
- Fixes picked individually after the last 4.14 release (marked with a `CVE:` line): ALSA usb-audio
  (Takashi Iwai, Benoît Sevens), posix-cpu-timers (Oleg Nesterov), HID core (Jiri Kosina) and
  uvcvideo (Benoit Sevens).
- Device bring-up, the LTS merges and their manual resolutions, the RKP-aware BPF JIT handling and
  the build fixes: lunar-seal, with AI assistance (Co-Authored-By: Claude trailers).
- Samsung's uH/RKP/KDP hypervisor support is disabled in the gts6l defconfig, as in the LineageOS
  Samsung kernels, so the RKP-aware BPF JIT code is present but inactive; fs-verity is enabled; the WPA3 nl80211 definition (Chung-Hsien Hsu) is backported from mainline.
