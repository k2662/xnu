 * Copyright (c) 2000-2016 Apple Inc. All rights reserved.
#include <machine/machine_routines.h>
#include <console/video_console.h>
extern void 		memory_object_mark_io_tracking(
	memory_object_control_t         control);
__private_extern__ int unlink1(vfs_context_t, vnode_t, user_addr_t,
    enum uio_seg, int);
static int unmount_callback(mount_t, __unused void *);

#if CONFIG_JETSAM && (DEVELOPMENT || DEBUG)
extern int bootarg_no_vnode_jetsam;    /* from bsd_init.c default value is 0 */
#endif /* CONFIG_JETSAM && (DEVELOPMENT || DEBUG) */

boolean_t root_is_CF_drive = FALSE;

		if ((flags & SKIPSYSTEM) && ((vp->v_flag & VSYSTEM) || (vp->v_flag & VNOFLUSH)))
		if ((flags & WRITECLOSE) && (vp->v_writecount == 0 || vp->v_type != VREG)) 

		if ((vp->v_usecount != 0) && ((vp->v_usecount - vp->v_kusecount) != 0)) {
			return 1;

		} else if (vp->v_iocount > 0) {
			 /* Busy if iocount is > 0 for more than 3 seconds */
			tsleep(&vp->v_iocount, PVFS, "vnode_drain_network", 3 * hz);
			if (vp->v_iocount > 0)
				return 1;
			continue;
	}
	return 0;
#include <i386/panic_hooks.h>

struct vnode_iterate_panic_hook {
	panic_hook_t hook;
	mount_t mp;
	struct vnode *vp;
};

static void vnode_iterate_panic_hook(panic_hook_t *hook_)
{
	extern int kdb_log(const char *fmt, ...);
	struct vnode_iterate_panic_hook *hook = (struct vnode_iterate_panic_hook *)hook_;
	panic_phys_range_t range;
	uint64_t phys;
	
	if (panic_phys_range_before(hook->mp, &phys, &range)) {
		kdb_log("mp = %p, phys = %p, prev (%p: %p-%p)\n", 
				hook->mp, phys, range.type, range.phys_start,
				range.phys_start + range.len);
	} else {
		kdb_log("mp = %p, phys = %p, prev (!)\n", hook->mp, phys);
	}

	if (panic_phys_range_before(hook->vp, &phys, &range)) {
		kdb_log("vp = %p, phys = %p, prev (%p: %p-%p)\n", 
				hook->vp, phys, range.type, range.phys_start,
				range.phys_start + range.len);
	} else {
		kdb_log("vp = %p, phys = %p, prev (!)\n", hook->vp, phys);
	}
	panic_dump_mem((void *)(((vm_offset_t)hook->mp -4096) & ~4095), 12288);
}


	struct vnode_iterate_panic_hook hook;
	hook.mp = mp;
	hook.vp = NULL;
	panic_hook(&hook.hook, vnode_iterate_panic_hook);
		hook.vp = vp;
	panic_unhook(&hook.hook);
		return (ENOENT);
	mount_lock(mp);
	if (mp->mnt_lflag & MNT_LUNMOUNT) {
		if (flags & LK_NOWAIT || mp->mnt_lflag & MNT_LDEAD) {

		/*
		 * Since all busy locks are shared except the exclusive
		 * lock granted when unmounting, the only place that a
		 * wakeup needs to be done is at the release of the
		 * exclusive lock at the end of dounmount.
		 */
		mp->mnt_lflag |= MNT_LWAIT;
		msleep((caddr_t)mp, &mp->mnt_mlock, (PVFS | PDROP), "vfsbusy", NULL);
		return (ENOENT);
	mount_unlock(mp);

	 * Until we are granted the rwlock, it's possible for the mount point to
	 * change state, so re-evaluate before granting the vfs_busy.
	strlcpy(mp->mnt_vfsstat.f_fstypename, vfsp->vfc_name, MFSTYPENAMELEN);
		if (vfsp->vfc_mountroot == NULL
			&& !ISSET(vfsp->vfc_vfsflags, VFC_VFSCANMOUNTROOT)) {
		}
		if (vfsp->vfc_mountroot)
			error = (*vfsp->vfc_mountroot)(mp, rootvp, ctx);
		else
			error = VFS_MOUNT(mp, rootvp, 0, ctx);

		if (!error) {
			if (mp->mnt_ioflags & MNT_IOFLAGS_FUSION_DRIVE) {
				root_is_CF_drive = TRUE;
			}

			uint32_t speed;

			if (MNTK_VIRTUALDEV & mp->mnt_kern_flag) speed = 128;
			else if (MNTK_SSD & mp->mnt_kern_flag)   speed = 7*256;
			else                                     speed = 256;
			vc_progress_setdiskspeed(speed);

				if ((vfsattr.f_capabilities.capabilities[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_DIR_HARDLINKS) &&
					(vfsattr.f_capabilities.valid[VOL_CAPABILITIES_FORMAT] & VOL_CAP_FMT_DIR_HARDLINKS)) {
					mp->mnt_kern_flag |= MNTK_DIR_HARDLINKS;
				}
	while (vfs_getvfs_locked(&tfsid)) {
		if (++mntid_gen == 0)
			mntid_gen++;
		tfsid.val[0] = makedev(nblkdev + mtype, mntid_gen);


boolean_t

again:

	/*
	 * In vclean, we might have deferred ditching locked buffers
	 * because something was still referencing them (indicated by
	 * usecount).  We can ditch them now.
	 */
	if (ISSET(vp->v_lflag, VL_DEAD)
		&& (!LIST_EMPTY(&vp->v_cleanblkhd) || !LIST_EMPTY(&vp->v_dirtyblkhd))) {
		++vp->v_iocount;	// Probably not necessary, but harmless
#ifdef JOE_DEBUG
		record_vp(vp, 1);
#endif
		vnode_unlock(vp);
		buf_invalidateblks(vp, BUF_INVALIDATE_LOCKED, 0, 0);
		vnode_lock(vp);
		vnode_dropiocount(vp);
		goto again;
	}

		if (--vp->v_writecount < 0)
			panic("vnode_rele_ext: vp %p writecount -ve : %d.  v_tag = %d, v_type = %d, v_flag = %x.", vp,  vp->v_writecount, vp->v_tag, vp->v_type, vp->v_flag);
		/*
		if (vp->v_usecount == 0) {
			vp->v_lflag |= VL_NEEDINACTIVE;
	if (ISSET(vp->v_lflag, VL_TERMINATE | VL_DEAD) || dont_reenter) {
		/*
		 * the filesystem on this release...in
		 * the latter case, we'll mark the vnode aged
		if (dont_reenter) {
			if ( !(vp->v_lflag & (VL_TERMINATE | VL_DEAD | VL_MARKTERM)) ) {
				vp->v_lflag |= VL_NEEDINACTIVE;
				if (vnode_on_reliable_media(vp) == FALSE || vp->v_flag & VISDIRTY) {
		vnode_list_add(vp);
		// If vnode is already terminating, wait for it...
		while (vp->v_id == vid && ISSET(vp->v_lflag, VL_TERMINATE)) {
			vp->v_lflag |= VL_TERMWANT;
			msleep(&vp->v_lflag, &vp->v_lock, PVFS, "vflush", NULL);
		}

		if ((vp->v_id != vid) || ISSET(vp->v_lflag, VL_DEAD)) {
			VNOP_FSYNC(vp, MNT_WAIT, ctx);

			/*
			 * If the vnode is still in use (by the journal for
			 * example) we don't want to invalidate locked buffers
			 * here.  In that case, either the journal will tidy them
			 * up, or we will deal with it when the usecount is
			 * finally released in vnode_rele_internal.
			 */
			buf_invalidateblks(vp, BUF_WRITE_DATA | (active ? 0 : BUF_INVALIDATE_LOCKED), 0, 0);
			vnode_relenamedstream(pvp, vp);
	 * (and in the case of forced unmount of an mmap-ed file,
	 * the ubc reference on the vnode is dropped here too).
	/*
	 * Remove the vnode from any mount list it might be on.  It is not
	 * safe to do this any earlier because unmount needs to wait for
	 * any vnodes to terminate and it cannot do that if it cannot find
	 * them.
	 */
	insmntque(vp, (struct mount *)0);

	vp->v_flag &= ~VISDIRTY;
				vnode_lock(vq);
				if (!(vq->v_lflag & VL_TERMINATE)) {
					vnode_reclaim_internal(vq, 1, 1, 0);
				}
				vnode_put_locked(vq);
				vnode_unlock(vq);
	vnode_lock(vp);
	if (vp->v_lflag & VL_TERMINATE) {
		vnode_unlock(vp);
		return (ENOENT);
	}
	vnode_reclaim_internal(vp, 1, 0, REVOKEALL);
	vnode_unlock(vp);
	if (!vnode_isspec(vp)) {
		return (vp->v_usecount - vp->v_kusecount);		
	}

int is_package_name(const char *name, int len)
/*
 * The VFS_NUMMNTOPS shouldn't be at name[1] since
 * is a VFS generic variable. Since we no longer support
 * VT_UFS, we reserve its value to support this sysctl node.
 *
 * It should have been:
 *    name[0]:  VFS_GENERIC
 *    name[1]:  VFS_NUMMNTOPS
 */
SYSCTL_INT(_vfs, VFS_NUMMNTOPS, nummntops,
		   CTLFLAG_RD | CTLFLAG_KERN | CTLFLAG_LOCKED,
		   &vfs_nummntops, 0, "");

int
vfs_sysctl(int *name __unused, u_int namelen __unused,
		   user_addr_t oldp __unused, size_t *oldlenp __unused,
           user_addr_t newp __unused, size_t newlen __unused, proc_t p __unused);

vfs_sysctl(int *name __unused, u_int namelen __unused,
		   user_addr_t oldp __unused, size_t *oldlenp __unused,
           user_addr_t newp __unused, size_t newlen __unused, proc_t p __unused)
	return (EINVAL);
}
//
// The following code disallows specific sysctl's that came through
// the direct sysctl interface (vfs_sysctl_node) instead of the newer
// sysctl_vfs_ctlbyfsid() interface.  We can not allow these selectors
// through vfs_sysctl_node() because it passes the user's oldp pointer
// directly to the file system which (for these selectors) casts it
// back to a struct sysctl_req and then proceed to use SYSCTL_IN()
// which jumps through an arbitrary function pointer.  When called
// through the sysctl_vfs_ctlbyfsid() interface this does not happen
// and so it's safe.
//
// Unfortunately we have to pull in definitions from AFP and SMB and
// perform explicit name checks on the file system to determine if
// these selectors are being used.
//
#define AFPFS_VFS_CTL_GETID            0x00020001
#define AFPFS_VFS_CTL_NETCHANGE        0x00020002
#define AFPFS_VFS_CTL_VOLCHANGE        0x00020003
#define SMBFS_SYSCTL_REMOUNT           1
#define SMBFS_SYSCTL_REMOUNT_INFO      2
#define SMBFS_SYSCTL_GET_SERVER_SHARE  3
static int
is_bad_sysctl_name(struct vfstable *vfsp, int selector_name)
{
	switch(selector_name) {
		case VFS_CTL_QUERY:
		case VFS_CTL_TIMEO:
		case VFS_CTL_NOLOCKS:
		case VFS_CTL_NSTATUS:
		case VFS_CTL_SADDR:
		case VFS_CTL_DISC:
		case VFS_CTL_SERVERINFO:
			return 1;
		default:
			break;
	// the more complicated check for some of SMB's special values
	if (strcmp(vfsp->vfc_name, "smbfs") == 0) {
		switch(selector_name) {
			case SMBFS_SYSCTL_REMOUNT:
			case SMBFS_SYSCTL_REMOUNT_INFO:
			case SMBFS_SYSCTL_GET_SERVER_SHARE:
				return 1;
		}
	} else if (strcmp(vfsp->vfc_name, "afpfs") == 0) {
		switch(selector_name) {
			case AFPFS_VFS_CTL_GETID:
			case AFPFS_VFS_CTL_NETCHANGE:
			case AFPFS_VFS_CTL_VOLCHANGE:
				return 1;
	//
	// If we get here we passed all the checks so the selector is ok
	//
	return 0;

int vfs_sysctl_node SYSCTL_HANDLER_ARGS
	int *name, namelen;
	struct vfstable *vfsp;
	int error;
	int fstypenum;
	
	fstypenum = oidp->oid_number;
	name = arg1;
	namelen = arg2;

	/* all sysctl names at this level should have at least one name slot for the FS */
	if (namelen < 1)
		return (EISDIR); /* overloaded */
	
	mount_list_lock();
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (vfsp->vfc_typenum == fstypenum) {
			vfsp->vfc_refcount++;
			break;
		}
	mount_list_unlock();
	
	if (vfsp == NULL) {
		return (ENOTSUP);
	}
	if (is_bad_sysctl_name(vfsp, name[0])) {
		printf("vfs: bad selector 0x%.8x for old-style sysctl().  use the sysctl-by-fsid interface instead\n", name[0]);
		return EPERM;
	}

	error = (vfsp->vfc_vfsops->vfs_sysctl)(name, namelen, req->oldptr, &req->oldlen, req->newptr, req->newlen, vfs_context_current());

	mount_list_lock();
	vfsp->vfc_refcount--;
	mount_list_unlock();
	return error;
}
struct unmount_info {
	int	u_errs;	// Total failed unmounts
	int	u_busy;	// EBUSY failed unmounts
};

static int
unmount_callback(mount_t mp, void *arg)
{
	int error;
	char *mntname;
	struct unmount_info *uip = arg;

	mount_ref(mp, 0);
	mount_iterdrop(mp);	// avoid vfs_iterate deadlock in dounmount()

	MALLOC_ZONE(mntname, void *, MAXPATHLEN, M_NAMEI, M_WAITOK);
	if (mntname)
		strlcpy(mntname, mp->mnt_vfsstat.f_mntonname, MAXPATHLEN);

	error = dounmount(mp, MNT_FORCE, 1, vfs_context_current());
	if (error) {
		uip->u_errs++;
		printf("Unmount of %s failed (%d)\n", mntname ? mntname:"?", error);
		if (error == EBUSY)
			uip->u_busy++;
	}
	if (mntname)
		FREE_ZONE(mntname, MAXPATHLEN, M_NAMEI);

	return (VFS_RETURNED);
}

 * Busy mounts are retried.
	int mounts, sec = 1;
	struct unmount_info ui;
retry:
	ui.u_errs = ui.u_busy = 0;
	vfs_iterate(VFS_ITERATE_CB_DROPREF | VFS_ITERATE_TAIL_FIRST, unmount_callback, &ui);
	mounts = mount_getvfscnt();
	if (mounts == 0)
		return;

	if (ui.u_busy > 0) {		// Busy mounts - wait & retry
		tsleep(&nummounts, PVFS, "busy mount", sec * hz);
		sec *= 2;
		if (sec <= 32)
			goto retry;
		printf("Unmounting timed out\n");
	} else if (ui.u_errs < mounts)	{
		// If the vfs_iterate missed mounts in progress - wait a bit
		tsleep(&nummounts, PVFS, "missed mount", 2 * hz);
	if (vp->v_usecount != 0) {
		/*
		 * At the eleventh hour, just before the ubcinfo is
		 * destroyed, ensure the ubc-specific v_usecount
		 * reference has gone.  We use v_usecount != 0 as a hint;
		 * ubc_unmap() does nothing if there's no mapping.
		 *
		 * This case is caused by coming here via forced unmount,
		 * versus the usual vm_object_deallocate() path.
		 * In the forced unmount case, ubc_destroy_named()
		 * releases the pager before memory_object_last_unmap()
		 * can be called.
		 */
		vnode_unlock(vp);
		ubc_unmap(vp);
		vnode_lock_spin(vp);
	}
#if CONFIG_IOSCHED
extern int lowpri_throttle_enabled;
extern int iosched_enabled;
#endif

	u_int32_t minsaturationbytecount = 0;
	u_int32_t ioqueue_depth = 0;
	dk_corestorage_info_t cs_info;
	boolean_t cs_present = FALSE;;
	mp->mnt_maxreadcnt = MAX_UPL_SIZE_BYTES;
	mp->mnt_maxwritecnt = MAX_UPL_SIZE_BYTES;
	if (VNOP_IOCTL(devvp, DKIOCGETIOMINSATURATIONBYTECOUNT, (caddr_t)&minsaturationbytecount, 0, ctx) == 0) {
		mp->mnt_minsaturationbytecount = minsaturationbytecount;
	} else {
		mp->mnt_minsaturationbytecount = 0;
	}

	if (VNOP_IOCTL(devvp, DKIOCCORESTORAGE, (caddr_t)&cs_info, 0, ctx) == 0)
		cs_present = TRUE;

	if (features & DK_FEATURE_UNMAP) {

		if (cs_present == TRUE)
			mp->mnt_ioflags |= MNT_IOFLAGS_CSUNMAP_SUPPORTED;
	}
	if (cs_present == TRUE) {
		/*
		 * for now we'll use the following test as a proxy for
		 * the underlying drive being FUSION in nature
		 */
		if ((cs_info.flags & DK_CORESTORAGE_PIN_YOUR_METADATA))
			mp->mnt_ioflags |= MNT_IOFLAGS_FUSION_DRIVE;
	}

#if CONFIG_IOSCHED
        if (iosched_enabled && (features & DK_FEATURE_PRIORITY)) {
                mp->mnt_ioflags |= MNT_IOFLAGS_IOSCHED_SUPPORTED;
		throttle_info_disable_throttle(mp->mnt_devbsdunit, (mp->mnt_ioflags & MNT_IOFLAGS_FUSION_DRIVE) != 0);
	}
#endif /* CONFIG_IOSCHED */
#ifdef NFSCLIENT
			} else
#endif
			{

#ifdef NFS_CLIENT
			} else
#endif
			{
static int	filt_fstouch(struct knote *kn, struct kevent_internal_s *kev);
static int	filt_fsprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev);
	.f_touch = filt_fstouch,
	.f_process = filt_fsprocess,

	/* 
	 * filter only sees future events, 
	 * so it can't be fired already.
	 */
filt_fstouch(struct knote *kn, struct kevent_internal_s *kev)
	int res;
	lck_mtx_lock(fs_klist_lock);
	kn->kn_sfflags = kev->fflags;
	if ((kn->kn_status & KN_UDATA_SPECIFIC) == 0)
		kn->kn_udata = kev->udata;
	/*
	 * the above filter function sets bits even if nobody is looking for them.
	 * Just preserve those bits even in the new mask is more selective
	 * than before.
	 *
	 * For compatibility with previous implementations, we leave kn_fflags
	 * as they were before.
	 */
	//if (kn->kn_sfflags)
	//	kn->kn_fflags &= kn->kn_sfflags;
	res = (kn->kn_fflags != 0);

	lck_mtx_unlock(fs_klist_lock);

	return res;
}

static int
filt_fsprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev)
{
#pragma unused(data)
	int res;

	lck_mtx_lock(fs_klist_lock);
	res = (kn->kn_fflags != 0);
	if (res) {
		*kev = kn->kn_kevent;
		kn->kn_flags |= EV_CLEAR; /* automatic */
		kn->kn_fflags = 0;
		kn->kn_data = 0;
	}
	lck_mtx_unlock(fs_klist_lock);
	return res;
}	

static int
sysctl_vfs_noremotehang(__unused struct sysctl_oid *oidp,
		__unused void *arg1, __unused int arg2, struct sysctl_req *req)
{
	int out, error;
	pid_t pid;
	proc_t p;

	/* We need a pid. */
	if (req->newptr == USER_ADDR_NULL)
		return (EINVAL);

	error = SYSCTL_IN(req, &pid, sizeof(pid));
	if (error)
		return (error);

	p = proc_find(pid < 0 ? -pid : pid);
	if (p == NULL)
static int
sysctl_vfs_generic_conf SYSCTL_HANDLER_ARGS
{
	int *name, namelen;
	struct vfstable *vfsp;
	struct vfsconf vfsc;
	
	(void)oidp;
	name = arg1;
	namelen = arg2;
	
	if (namelen < 1) {
		return (EISDIR);
	} else if (namelen > 1) {
		return (ENOTDIR);
	}
			
	mount_list_lock();
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (vfsp->vfc_typenum == name[0])
			break;
	
	if (vfsp == NULL) {
		mount_list_unlock();
		return (ENOTSUP);
	}
			
	vfsc.vfc_reserved1 = 0;
	bcopy(vfsp->vfc_name, vfsc.vfc_name, sizeof(vfsc.vfc_name));
	vfsc.vfc_typenum = vfsp->vfc_typenum;
	vfsc.vfc_refcount = vfsp->vfc_refcount;
	vfsc.vfc_flags = vfsp->vfc_flags;
	vfsc.vfc_reserved2 = 0;
	vfsc.vfc_reserved3 = 0;
			
	mount_list_unlock();
	return (SYSCTL_OUT(req, &vfsc, sizeof(struct vfsconf)));
}

SYSCTL_PROC(_vfs_generic, OID_AUTO, vfsidlist,
    CTLTYPE_STRUCT | CTLFLAG_RD | CTLFLAG_LOCKED,
SYSCTL_INT(_vfs_generic, VFS_MAXTYPENUM, maxtypenum,
		   CTLFLAG_RD | CTLFLAG_KERN | CTLFLAG_LOCKED,
		   &maxvfstypenum, 0, "");
SYSCTL_INT(_vfs_generic, OID_AUTO, sync_timeout, CTLFLAG_RW | CTLFLAG_LOCKED, &sync_timeout, 0, "");
SYSCTL_NODE(_vfs_generic, VFS_CONF, conf,
		   CTLFLAG_RD | CTLFLAG_LOCKED,
		   sysctl_vfs_generic_conf, "");

/*
 * Print vnode state.
 */
void
vn_print_state(struct vnode *vp, const char *fmt, ...)
{
	va_list ap;
	char perm_str[] = "(VM_KERNEL_ADDRPERM pointer)";
	char fs_name[MFSNAMELEN];

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("vp 0x%0llx %s: ", (uint64_t)VM_KERNEL_ADDRPERM(vp), perm_str);
	printf("tag %d, type %d\n", vp->v_tag, vp->v_type);
	/* Counts .. */
	printf("    iocount %d, usecount %d, kusecount %d references %d\n",
	    vp->v_iocount, vp->v_usecount, vp->v_kusecount, vp->v_references);
	printf("    writecount %d, numoutput %d\n", vp->v_writecount,
	    vp->v_numoutput);
	/* Flags */
	printf("    flag 0x%x, lflag 0x%x, listflag 0x%x\n", vp->v_flag,
	    vp->v_lflag, vp->v_listflag);

	if (vp->v_mount == NULL || vp->v_mount == dead_mountp) {
		strlcpy(fs_name, "deadfs", MFSNAMELEN);
	} else {
		vfs_name(vp->v_mount, fs_name);
	}

	printf("    v_data 0x%0llx %s\n",
	    (vp->v_data ? (uint64_t)VM_KERNEL_ADDRPERM(vp->v_data) : 0),
	    perm_str);
	printf("    v_mount 0x%0llx %s vfs_name %s\n",
	    (vp->v_mount ? (uint64_t)VM_KERNEL_ADDRPERM(vp->v_mount) : 0),
	    perm_str, fs_name);
}

		if (want_vp && (vnode_on_reliable_media(vp) == FALSE || (vp->v_flag & VISDIRTY))) {
			if ( !LIST_EMPTY(&vp->v_nclinks) || !TAILQ_EMPTY(&vp->v_ncchildren))
__attribute__((noreturn))
		TAILQ_INIT(&vp->v_ncchildren);

			"%d free, %d dead, %d async, %d rage\n",
		        desiredvnodes, numvnodes, freevnodes, deadvnodes, async_work_vnodes, ragevnodes);

#if DEVELOPMENT || DEBUG
		if (bootarg_no_vnode_jetsam)
			panic("vnode table is full\n");
#endif /* DEVELOPMENT || DEBUG */

		if (memorystatus_kill_on_vnode_limit() == FALSE) {
static inline void
vn_set_dead(vnode_t vp)
{
	vp->v_mount = NULL;
	vp->v_op = dead_vnodeop_p;
	vp->v_tag = VT_NON;
	vp->v_data = NULL;
	vp->v_type = VBAD;
	vp->v_lflag |= VL_DEAD;
}

int vnode_usecount(vnode_t vp)
{
	return vp->v_usecount;
}

int vnode_iocount(vnode_t vp)
{
	return vp->v_iocount;
}
 * However, if the vnode is marked DIRTY, we want to pull it out much earlier
#define UNAGE_THRESHHOLD        25
#define UNAGE_DIRTYTHRESHHOLD    6    
	int withvid = vflags & VNODE_WITHID;
		int sleepflg = 0;

		 * If this vnode is getting drained, there are some cases where
		 * we can't block or, in case of tty vnodes, want to be
		 * interruptible.
		if (vp->v_lflag & VL_DRAIN) {
			/*
			 * In some situations, we want to get an iocount
			 * even if the vnode is draining to prevent deadlock,
			 * e.g. if we're in the filesystem, potentially holding
			 * resources that could prevent other iocounts from
			 * being released.
			 */
			if (beatdrain)
				break;
			/*
			 * Don't block if the vnode's mount point is unmounting as
			 * we may be the thread the unmount is itself waiting on
			 * Only callers who pass in vids (at this point, we've already
			 * handled nosusp and nodead) are expecting error returns
			 * from this function, so only we can only return errors for
			 * those. ENODEV is intended to inform callers that the call
			 * failed because an unmount is in progress.
			 */
			if (withvid && (vp->v_mount) && vfs_isunmount(vp->v_mount))
				return (ENODEV);

			if (vnode_istty(vp)) {
				sleepflg = PCATCH;
			}
			int error;

			error = msleep(&vp->v_lflag,   &vp->v_lock,
			   (PVFS | sleepflg), "vnode getiocount", NULL);
			if (error)
				return (error);
	if (withvid && vid != vp->v_id) {
	if (++vp->v_references >= UNAGE_THRESHHOLD ||
	    (vp->v_flag & VISDIRTY && vp->v_references >= UNAGE_DIRTYTHRESHHOLD)) {
static int
vnode_create_internal(uint32_t flavor, uint32_t size, void *data, vnode_t *vpp,
    int init_vnode)
	int existing_vnode;
	if (*vpp) {
		vp = *vpp;
		*vpp = NULLVP;
		existing_vnode = 1;
	} else {
		existing_vnode = 0;
	}
	if (init_vnode) {
		/* Do quick sanity check on the parameters. */
		if ((param == NULL) || (param->vnfs_vtype == VBAD)) {
			error = EINVAL;
			goto error_out;
		}
#if CONFIG_TRIGGERS
		if ((flavor == VNCREATE_TRIGGER) && (size == VNCREATE_TRIGGER_SIZE)) {
			tinfo = (struct vnode_trigger_param *)data;

			/* Validate trigger vnode input */
			if ((param->vnfs_vtype != VDIR) ||
			    (tinfo->vnt_resolve_func == NULL) ||
			    (tinfo->vnt_flags & ~VNT_VALID_MASK)) {
				error = EINVAL;
				goto error_out;
			}
			/* Fall through a normal create (params will be the same) */
			flavor = VNCREATE_FLAVOR;
			size = VCREATESIZE;
		if ((flavor != VNCREATE_FLAVOR) || (size != VCREATESIZE)) {
			error = EINVAL;
			goto error_out;
		}
	}
	if (!existing_vnode) {
		if ((error = new_vnode(&vp)) ) {
			return (error);
		}
		if (!init_vnode) {
			/* Make it so that it can be released by a vnode_put) */
			vn_set_dead(vp);
			*vpp = vp;
			return (0);
		}
	} else {
		/*
		 * A vnode obtained by vnode_create_empty has been passed to
		 * vnode_initialize - Unset VL_DEAD set by vn_set_dead. After
		 * this point, it is set back on any error.
		 *
		 * N.B. vnode locking - We make the same assumptions as the
		 * "unsplit" vnode_create did - i.e. it is safe to update the
		 * vnode's fields without the vnode lock. This vnode has been
		 * out and about with the filesystem and hopefully nothing
		 * was done to the vnode between the vnode_create_empty and
		 * now when it has come in through vnode_initialize.
		 */
		vp->v_lflag &= ~VL_DEAD;
	}
			vn_set_dead(vp);
		if (param->vnfs_mp->mnt_ioflags & MNT_IOFLAGS_IOSCHED_SUPPORTED)
			memory_object_mark_io_tracking(vp->v_ubcinfo->ui_control);
			vn_set_dead(vp);
			if (maj < (u_int)nchrdev && cdevsw[maj].d_type == D_TTY)

#if CONFIG_SECLUDED_MEMORY
	switch (secluded_for_filecache) {
	case 0:
		/*
		 * secluded_for_filecache == 0:
		 * + no file contents in secluded pool
		 */
		break;
	case 1:
		/*
		 * secluded_for_filecache == 1:
		 * + no files from /
		 * + files from /Applications/ are OK
		 * + files from /Applications/Camera are not OK
		 * + no files that are open for write
		 */
		if (vnode_vtype(vp) == VREG &&
		    vnode_mount(vp) != NULL &&
		    (! (vfs_flags(vnode_mount(vp)) & MNT_ROOTFS))) {
			/* not from root filesystem: eligible for secluded pages */
			memory_object_mark_eligible_for_secluded(
				ubc_getobject(vp, UBC_FLAGS_NONE),
				TRUE);
		}
		break;
	case 2:
		/*
		 * secluded_for_filecache == 2:
		 * + all read-only files OK, except:
		 * 	+ dyld_shared_cache_arm64*
		 * 	+ Camera
		 *	+ mediaserverd
		 */
		if (vnode_vtype(vp) == VREG) {
			memory_object_mark_eligible_for_secluded(
				ubc_getobject(vp, UBC_FLAGS_NONE),
				TRUE);
		}
		break;
	default:
		break;
	}
#endif /* CONFIG_SECLUDED_MEMORY */


error_out:
	if (existing_vnode) {
		vnode_put(vp);
	}
	return (error);
}

/* USAGE:
 * The following api creates a vnode and associates all the parameter specified in vnode_fsparam
 * structure and returns a vnode handle with a reference. device aliasing is handled here so checkalias
 * is obsoleted by this.
 */
int
vnode_create(uint32_t flavor, uint32_t size, void *data, vnode_t *vpp)
{
	*vpp = NULLVP;
	return (vnode_create_internal(flavor, size, data, vpp, 1));
}

int
vnode_create_empty(vnode_t *vpp)
{
	*vpp = NULLVP;
	return (vnode_create_internal(VNCREATE_FLAVOR, VCREATESIZE, NULL,
	    vpp, 0));
}

int
vnode_initialize(uint32_t flavor, uint32_t size, void *data, vnode_t *vpp)
{
	if (*vpp == NULLVP) {
		panic("NULL vnode passed to vnode_initialize");
	}
#if DEVELOPMENT || DEBUG
	/*
	 * We lock to check that vnode is fit for unlocked use in
	 * vnode_create_internal.
	 */
	vnode_lock_spin(*vpp);
	VNASSERT(((*vpp)->v_iocount == 1), *vpp,
	    ("vnode_initialize : iocount not 1, is %d", (*vpp)->v_iocount));
	VNASSERT(((*vpp)->v_usecount == 0), *vpp,
	    ("vnode_initialize : usecount not 0, is %d", (*vpp)->v_usecount));
	VNASSERT(((*vpp)->v_lflag & VL_DEAD), *vpp,
	    ("vnode_initialize : v_lflag does not have VL_DEAD, is 0x%x",
	    (*vpp)->v_lflag));
	VNASSERT(((*vpp)->v_data == NULL), *vpp,
	    ("vnode_initialize : v_data not NULL"));
	vnode_unlock(*vpp);
#endif
	return (vnode_create_internal(flavor, size, data, vpp, 1));
	int cb_dropref = (flags & VFS_ITERATE_CB_DROPREF);
		/*
		 * Drop the iterref here if the callback didn't do it.
		 * Note: If cb_dropref is set the mp may no longer exist.
		 */
		if (!cb_dropref)
			mount_iterdrop(mp);
	if (ctx == NULL) {
		return EINVAL;

	if (flags & VNODE_LOOKUP_CROSSMOUNTNOWAIT)
		ndflags |= CN_NBMOUNTLOOK;
	if (lflags & VNODE_LOOKUP_CROSSMOUNTNOWAIT)
		ndflags |= CN_NBMOUNTLOOK;

errno_t
vnode_mtime(vnode_t vp, struct timespec *mtime, vfs_context_t ctx)
{
	struct vnode_attr	va;
	int			error;

	VATTR_INIT(&va);
	VATTR_WANTED(&va, va_modify_time);
	error = vnode_getattr(vp, &va, ctx);
	if (!error)
		*mtime = va.va_modify_time;
	return error;
}

errno_t
vnode_flags(vnode_t vp, uint32_t *flags, vfs_context_t ctx)
{
	struct vnode_attr	va;
	int			error;

	VATTR_INIT(&va);
	VATTR_WANTED(&va, va_flags);
	error = vnode_getattr(vp, &va, ctx);
	if (!error)
		*flags = va.va_flags;
	return error;
}

int
vnode_setdirty(vnode_t vp)
{
	vnode_lock_spin(vp);
	vp->v_flag |= VISDIRTY;
	vnode_unlock(vp);
	return 0;
}

int
vnode_cleardirty(vnode_t vp)
{
	vnode_lock_spin(vp);
	vp->v_flag &= ~VISDIRTY;
	vnode_unlock(vp);
	return 0;
}

int 
vnode_isdirty(vnode_t vp)
{
	int dirty;

	vnode_lock_spin(vp);
	dirty = (vp->v_flag & VISDIRTY) ? 1 : 0;
	vnode_unlock(vp);

	return dirty;
}

		return VNOP_COMPOUND_OPEN(dvp, vpp, ndp, O_CREAT, fmode, statusp, vap, ctx);

#if !CONFIG_MACF
#pragma unused(cnp)
#endif
			!(vp->v_mount->mnt_kern_flag & MNTK_DIR_HARDLINKS)) {
	error = vnode_authorize(vp, NULL, action, ctx);
#if NAMEDSTREAMS
	if (error == EACCES) {
		/*
		 * Shadow files may exist on-disk with a different UID/GID
		 * than that of the current context.  Verify that this file
		 * is really a shadow file.  If it was created successfully
		 * then it should be authorized.
		 */
		if (vnode_isshadow(vp) && vnode_isnamedstream (vp)) {
			error = vnode_verifynamedstream(vp);
		}
	}
#endif

	return error;
#if !CONFIG_MACF
#pragma unused(vap)
#endif
int
					struct vnode *tdvp,  struct vnode *tvp,  struct componentname *tcnp,
					vfs_context_t ctx, void *reserved)
{
	return vn_authorize_renamex(fdvp, fvp, fcnp, tdvp, tvp, tcnp, ctx, 0, reserved);
}

int
vn_authorize_renamex(struct vnode *fdvp,  struct vnode *fvp,  struct componentname *fcnp,
					 struct vnode *tdvp,  struct vnode *tvp,  struct componentname *tcnp,
					 vfs_context_t ctx, vfs_rename_flags_t flags, void *reserved)
	bool swap = flags & VFS_RENAME_SWAP;
	error = mac_vnode_check_rename(ctx, fdvp, fvp, fcnp, tdvp, tvp, tcnp);
	if (swap) {
		error = mac_vnode_check_rename(ctx, tdvp, tvp, tcnp, fdvp, fvp, fcnp);
		if (error)
			goto out;
	}
		if (!swap) {
			if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
				error = ENOTDIR;
				goto out;
			} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
				error = EISDIR;
				goto out;
			}
	} else if (swap) {
		/*
		 * Caller should have already checked this and returned
		 * ENOENT.  If we send back ENOENT here, caller will retry
		 * which isn't what we want so we send back EINVAL here
		 * instead.
		 */
		error = EINVAL;
		goto out;

	if (swap && fdvp->v_parent == tvp) {
		error = EINVAL;
		goto out;
	}
	if (swap) {
		kauth_action_t f = 0, t = 0;
		/*
		 * Directories changing parents need ...ADD_SUBDIR...  to
		 * permit changing ".."
		 */
		if (fdvp != tdvp) {
			if (vnode_isdir(fvp))
				f = KAUTH_VNODE_ADD_SUBDIRECTORY;
			if (vnode_isdir(tvp))
				t = KAUTH_VNODE_ADD_SUBDIRECTORY;
		}
		error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | f, ctx);
		if (error)
		error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE | t, ctx);
		if (error)
		f = vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE;
		t = vnode_isdir(tvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE;
		if (fdvp == tdvp)
			error = vnode_authorize(fdvp, NULL, f | t, ctx);
		else {
			error = vnode_authorize(fdvp, NULL, t, ctx);
			if (error)
				goto out;
			error = vnode_authorize(tdvp, NULL, f, ctx);
		if (error)
			goto out;
		error = 0;
		if ((tvp != NULL) && vnode_isdir(tvp)) {
			if (tvp != fdvp)
				moving = 1;
		} else if (tdvp != fdvp) {
			moving = 1;
		}

		/*
		 * must have delete rights to remove the old name even in
		 * the simple case of fdvp == tdvp.
		 *
		 * If fvp is a directory, and we are changing it's parent,
		 * then we also need rights to rewrite its ".." entry as well.
		 */
		if (vnode_isdir(fvp)) {
			if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | KAUTH_VNODE_ADD_SUBDIRECTORY, ctx)) != 0)
				goto out;
		} else {
			if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE, ctx)) != 0)
				goto out;
		}
		if (moving) {
			/* moving into tdvp or tvp, must have rights to add */
			if ((error = vnode_authorize(((tvp != NULL) && vnode_isdir(tvp)) ? tvp : tdvp,
							NULL, 
							vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE,
							ctx)) != 0) {
				goto out;
			}
		} else {
			/* node staying in same directory, must be allowed to add new name */
			if ((error = vnode_authorize(fdvp, NULL,
							vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE, ctx)) != 0)
				goto out;
		}
		/* overwriting tvp */
		if ((tvp != NULL) && !vnode_isdir(tvp) &&
				((error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE, ctx)) != 0)) {
		}
#if !CONFIG_MACF
#pragma unused(vap)
#endif
#if CONFIG_MACF
#else
#pragma unused(cnp)
#endif
 * The precedence of factors for authorizing or denying delete for a credential
 *
 * 1) Explicit ACE on the node. (allow or deny DELETE)
 * 2) Explicit ACE on the directory (allow or deny DELETE_CHILD).
 *
 *    If there are conflicting ACEs on the node and the directory, the node
 *    ACE wins.
 *
 * 3) Sticky bit on the directory.
 *    Deletion is not permitted if the directory is sticky and the caller is
 *    not owner of the node or directory. The sticky bit rules are like a deny
 *    delete ACE except lower in priority than ACL's either allowing or denying
 *    delete.
 * 4) POSIX permisions on the directory.
 * on directories. This enables us to skip directory ACL and POSIX checks
 * as we already have the result from those checks. However, we always check the
 * node ACL and, if the directory has the sticky bit set, we always check its
 * ACL (even for a directory with an authorized delete child). Furthermore,
 * caching the delete child authorization is independent of the sticky bit
 * being set as it is only applicable in determining whether the node can be
 * deleted or not.
static int
	int			error, ismember;

	/* Check the ACL on the node first */
	if (VATTR_IS_NOT(vap, va_acl, NULL)) {
		eval.ae_requested = KAUTH_VNODE_DELETE;
		eval.ae_acl = &vap->va_acl->acl_ace[0];
		eval.ae_count = vap->va_acl->acl_entrycount;
		eval.ae_options = 0;
		if (vauth_file_owner(vcp))
			eval.ae_options |= KAUTH_AEVAL_IS_OWNER;
		/*
		 * We use ENOENT as a marker to indicate we could not get
		 * information in order to delay evaluation until after we
		 * have the ACL evaluation answer.  Previously, we would
		 * always deny the operation at this point.
		 */
		if ((error = vauth_file_ingroup(vcp, &ismember, ENOENT)) != 0 && error != ENOENT)
			return (error);
		if (error == ENOENT)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP_UNKNOWN;
		else if (ismember)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP;
		eval.ae_exp_gall = KAUTH_VNODE_GENERIC_ALL_BITS;
		eval.ae_exp_gread = KAUTH_VNODE_GENERIC_READ_BITS;
		eval.ae_exp_gwrite = KAUTH_VNODE_GENERIC_WRITE_BITS;
		eval.ae_exp_gexec = KAUTH_VNODE_GENERIC_EXECUTE_BITS;

		if ((error = kauth_acl_evaluate(cred, &eval)) != 0) {
			KAUTH_DEBUG("%p    ERROR during ACL processing - %d", vcp->vp, error);
			return (error);
		}

		switch(eval.ae_result) {
		case KAUTH_RESULT_DENY:
			KAUTH_DEBUG("%p    DENIED - denied by ACL", vcp->vp);
			return (EACCES);
		case KAUTH_RESULT_ALLOW:
			KAUTH_DEBUG("%p    ALLOWED - granted by ACL", vcp->vp);
			return (0);
		case KAUTH_RESULT_DEFER:
		default:
			/* Defer to directory */
			KAUTH_DEBUG("%p    DEFERRED - by file ACL", vcp->vp);
			break;
		}
	}

	/*
	 * Without a sticky bit, a previously authorized delete child is
	 * sufficient to authorize this delete.
	 *
	 * If the sticky bit is set, a directory ACL which allows delete child
	 * overrides a (potential) sticky bit deny. The authorized delete child
	 * cannot tell us if it was authorized because of an explicit delete
	 * child allow ACE or because of POSIX permisions so we have to check
	 * the directory ACL everytime if the directory has a sticky bit.
	 */
	if (!(dvap->va_mode & S_ISTXT) && cached_delete_child) {
		KAUTH_DEBUG("%p    ALLOWED - granted by directory ACL or POSIX permissions and no sticky bit on directory", vcp->vp);
		return (0);
	}
	if (VATTR_IS_NOT(dvap, va_acl, NULL)) {
			return (error);
			KAUTH_DEBUG("%p    DENIED - denied by directory ACL", vcp->vp);
			return (EACCES);
		case KAUTH_RESULT_ALLOW:
			KAUTH_DEBUG("%p    ALLOWED - granted by directory ACL", vcp->vp);
			if (!cached_delete_child && vcp->dvp) {
				vnode_cache_authorized_action(vcp->dvp,
				    vcp->ctx, KAUTH_VNODE_DELETE_CHILD);
			}
			return (0);
			/* Deferred by directory ACL */
	/*
	 * From this point, we can't explicitly allow and if we reach the end
	 * of the function without a denial, then the delete is authorized.
	 */
	if (!cached_delete_child) {
		if (vnode_authorize_posix(vcp, VWRITE, 1 /* on_dir */) != 0) {
			KAUTH_DEBUG("%p    DENIED - denied by posix permisssions", vcp->vp);
			return (EACCES);
		}
		 * Cache the authorized action on the vnode if allowed by the
		 * directory ACL or POSIX permissions. It is correct to cache
		 * this action even if sticky bit would deny deleting the node.
		if (vcp->dvp) {
			vnode_cache_authorized_action(vcp->dvp, vcp->ctx,
			    KAUTH_VNODE_DELETE_CHILD);
		return (EACCES);
	return (0);
	boolean_t		is_suser = FALSE;
	 * If the vnode is a namedstream (extended attribute) data vnode (eg.
	 * a resource fork), *_DATA becomes *_EXTATTRIBUTES.

		/*
		 * Point 'vp' to the namedstream's parent for ACL checking
		 */
		if ((vp->v_parent != NULL) &&
		    (vget_internal(vp->v_parent, 0, VNODE_NODEAD | VNODE_DRAINO) == 0)) {
			parent_ref = TRUE;
			vcp->vp = vp = vp->v_parent;
		}
	}

	if (vfs_context_issuser(ctx)) {
		/*
		 * if we're not asking for execute permissions or modifications,
		 * then we're done, this action is authorized.
		 */
		if (!(rights & (KAUTH_VNODE_EXECUTE | KAUTH_VNODE_WRITE_RIGHTS)))
			goto success;

		is_suser = TRUE;
	 * Get vnode attributes and extended security information for the vnode
	 * and directory if required.
	 *
	 * If we're root we only want mode bits and flags for checking
	 * execute and immutability.
	VATTR_WANTED(&va, va_mode);
	VATTR_WANTED(&va, va_flags);
	if (!is_suser) {
	}
	if ((result = vnode_getattr(vp, &va, ctx)) != 0) {
		KAUTH_DEBUG("%p    ERROR - failed to get vnode attributes - %d", vp, result);
		goto out;
	}
	if (dvp) {
		VATTR_WANTED(&dva, va_mode);
		VATTR_WANTED(&dva, va_flags);
		if (!is_suser) {
			VATTR_WANTED(&dva, va_uid);
			VATTR_WANTED(&dva, va_gid);
			VATTR_WANTED(&dva, va_acl);
		}
		if ((result = vnode_getattr(dvp, &dva, ctx)) != 0) {
			KAUTH_DEBUG("%p    ERROR - failed to get directory vnode attributes - %d", vp, result);
		}
	if (!is_suser) {
		/* Assume that there were DENYs so we don't wrongly cache KAUTH_VNODE_SEARCHBYANYONE */
		found_deny = TRUE;
		
		 *
		 * Note that we can correctly cache KAUTH_VNODE_SEARCHBYANYONE
		 * only if we actually check ACLs which we don't for root. As
		 * a workaround, the lookup fast path checks for root.
success:

	int		has_priv_suser, ismember, defaulted_owner, defaulted_group, defaulted_mode, inherit_restricted;
	struct vnode_attr dva;
	inherit_restricted = 0;

	/*
	 * We need the dvp's va_flags and *may* need the gid of the directory,
	 * we ask for both here.
	 */
	VATTR_INIT(&dva);
	VATTR_WANTED(&dva, va_gid);
	VATTR_WANTED(&dva, va_flags);
	if ((error = vnode_getattr(dvp, &dva, ctx)) != 0)
		goto out;


	/* Determine if SF_RESTRICTED should be inherited from the parent
	 * directory. */
	if (VATTR_IS_SUPPORTED(&dva, va_flags) &&
	    (dva.va_flags & SF_RESTRICTED)) {
		inherit_restricted = 1;
	}

	if (inherit_restricted) {
		/* Apply SF_RESTRICTED to the file if its parent directory was
		 * restricted.  This is done at the end so that root is not
		 * required if this flag is only set due to inheritance. */
		VATTR_SET(vap, va_flags, (vap->va_flags | SF_RESTRICTED));
	}
		/* size is only meaningful on regular files, don't permit otherwise */
		if (!vnode_isreg(vp)) {
			KAUTH_DEBUG("ATTR - ERROR: size change requested on non-file");
			error = vnode_isdir(vp) ? EISDIR : EINVAL;
		}
			
		/*
		 * clear set-uid and set-gid bits. POSIX only requires this for
		 * non-privileged processes but we do it even for root.
		 */
		if (VATTR_IS_ACTIVE(vap, va_mode)) {
			newmode = vap->va_mode;
		} else if (VATTR_IS_SUPPORTED(&ova, va_mode)) {
			newmode = ova.va_mode;
		} else {
			KAUTH_DEBUG("CHOWN - trying to change owner but cannot get mode from filesystem to mask setugid bits");
			newmode = 0;
		}

		/* chown always clears setuid/gid bits. An exception is made for
		 * setattrlist executed by a root process to set <uid, gid, mode> on a file:
		 * setattrlist is allowed to set the new mode on the file and change (chown)
		 * uid/gid.
		 */
		if (newmode & (S_ISUID | S_ISGID)) {
			if (!VATTR_IS_ACTIVE(vap, va_mode) || !has_priv_suser) {
				KAUTH_DEBUG("CHOWN - masking setugid bits from mode %o to %o",
					newmode, newmode & ~(S_ISUID | S_ISGID));
				newmode &= ~(S_ISUID | S_ISGID);
			VATTR_SET(vap, va_mode, newmode);
vfs_setcompoundopen(mount_t mp)
	mp->mnt_compound_ops |= COMPOUND_VNOP_OPEN;

vnode_setswapmount(vnode_t vp)
	mount_lock(vp->v_mount);
	vp->v_mount->mnt_kern_flag |= MNTK_SWAP_MOUNT;
	mount_unlock(vp->v_mount);
}


int64_t
vnode_getswappin_avail(vnode_t vp)
{
	int64_t	max_swappin_avail = 0;

	mount_lock(vp->v_mount);
	if (vp->v_mount->mnt_ioflags & MNT_IOFLAGS_SWAPPIN_SUPPORTED)
		max_swappin_avail = vp->v_mount->mnt_max_swappin_available;
	mount_unlock(vp->v_mount);

	return (max_swappin_avail);

	char *rbuf = NULL;
   	void *dir_pos;
	void *dir_end;
		return (error);
		dir_pos = (void*) rbuf;
		dir_end = (void*) (rbuf + siz);
		dp = (struct dirent*) (dir_pos);
		if (dir_pos == dir_end)
		while (dir_pos < dir_end) {
			dir_pos = (void*) ((uint8_t*)dir_pos + dp->d_reclen);
			dp = (struct dirent*)dir_pos;
		dir_pos = (void*) rbuf;
		dir_end = (void*) (rbuf + siz);
		dp = (struct dirent*) dir_pos;
		if (dir_pos == dir_end)
		while (dir_pos < dir_end) {
				error = unlink1(ctx, vp,
				    CAST_USER_ADDR_T(dp->d_name), UIO_SYSSPACE,
				    VNODE_REMOVE_SKIP_NAMESPACE_EVENT |
				    VNODE_REMOVE_NO_AUDIT_PATH);
			dir_pos = (void*) ((uint8_t*)dir_pos + dp->d_reclen);
			dp = (struct dirent*)dir_pos;
	if (auio)
		uio_free(auio);
void panic_print_vnodes(void);

/* define PANIC_PRINTS_VNODES only if investigation is required. */
#ifdef PANIC_PRINTS_VNODES

static const char *__vtype(uint16_t vtype)
{
	switch (vtype) {
	case VREG:
		return "R";
	case VDIR:
		return "D";
	case VBLK:
		return "B";
	case VCHR:
		return "C";
	case VLNK:
		return "L";
	case VSOCK:
		return "S";
	case VFIFO:
		return "F";
	case VBAD:
		return "x";
	case VSTR:
		return "T";
	case VCPLX:
		return "X";
	default:
		return "?";
	}
}

/*
 * build a path from the bottom up
 * NOTE: called from the panic path - no alloc'ing of memory and no locks!
 */
static char *__vpath(vnode_t vp, char *str, int len, int depth)
{
	int vnm_len;
	const char *src;
	char *dst;

	if (len <= 0)
		return str;
	/* str + len is the start of the string we created */
	if (!vp->v_name)
		return str + len;

	/* follow mount vnodes to get the full path */
	if ((vp->v_flag & VROOT)) {
		if (vp->v_mount != NULL && vp->v_mount->mnt_vnodecovered) {
			return __vpath(vp->v_mount->mnt_vnodecovered,
				       str, len, depth+1);
		}
		return str + len;
	}

	src = vp->v_name;
	vnm_len = strlen(src);
	if (vnm_len > len) {
		/* truncate the name to fit in the string */
		src += (vnm_len - len);
		vnm_len = len;
	}

	/* start from the back and copy just characters (no NULLs) */

	/* this will chop off leaf path (file) names */
	if (depth > 0) {
		dst = str + len - vnm_len;
		memcpy(dst, src, vnm_len);
		len -= vnm_len;
	} else {
		dst = str + len;
	}

	if (vp->v_parent && len > 1) {
		/* follow parents up the chain */
		len--;
		*(dst-1) = '/';
		return __vpath(vp->v_parent, str, len, depth + 1);
	}

	return dst;
}

extern int kdb_printf(const char *format, ...) __printflike(1,2);

#define SANE_VNODE_PRINT_LIMIT 5000
void panic_print_vnodes(void)
{
	mount_t mnt;
	vnode_t vp;
	int nvnodes = 0;
	const char *type;
	char *nm;
	char vname[257];

	kdb_printf("\n***** VNODES *****\n"
		   "TYPE UREF ICNT PATH\n");

	/* NULL-terminate the path name */
	vname[sizeof(vname)-1] = '\0';

	/*
	 * iterate all vnodelist items in all mounts (mntlist) -> mnt_vnodelist
	 */
	TAILQ_FOREACH(mnt, &mountlist, mnt_list) {

		if (!ml_validate_nofault((vm_offset_t)mnt, sizeof(mount_t))) {
			kdb_printf("Unable to iterate the mount list %p - encountered an invalid mount pointer %p \n",
				&mountlist, mnt);
			break;
		}

		TAILQ_FOREACH(vp, &mnt->mnt_vnodelist, v_mntvnodes) {

			if (!ml_validate_nofault((vm_offset_t)vp, sizeof(vnode_t))) {
				kdb_printf("Unable to iterate the vnode list %p - encountered an invalid vnode pointer %p \n",
					&mnt->mnt_vnodelist, vp);
				break;
			}
				
			if (++nvnodes > SANE_VNODE_PRINT_LIMIT)
				return;
			type = __vtype(vp->v_type);
			nm = __vpath(vp, vname, sizeof(vname)-1, 0);
			kdb_printf("%s %0d %0d %s\n",
				   type, vp->v_usecount, vp->v_iocount, nm);
		}
	}
}

#else /* !PANIC_PRINTS_VNODES */
void panic_print_vnodes(void)
{
	return;
}
#endif



vm_offset_t kdebug_vnode(vnode_t vp)
{
	return VM_KERNEL_ADDRPERM(vp);
}

static int flush_cache_on_write = 0;
SYSCTL_INT (_kern, OID_AUTO, flush_cache_on_write,
			CTLFLAG_RW | CTLFLAG_LOCKED, &flush_cache_on_write, 0,
			"always flush the drive cache on writes to uncached files");

int vnode_should_flush_after_write(vnode_t vp, int ioflag)
{
	return (flush_cache_on_write
			&& (ISSET(ioflag, IO_NOCACHE) || vnode_isnocache(vp)));
}

/*
 * sysctl for use by disk I/O tracing tools to get the list of existing
 * vnodes' paths
 */

struct vnode_trace_paths_context {
	uint64_t count;
	long path[MAXPATHLEN / sizeof (long) + 1]; /* + 1 in case sizeof (long) does not divide MAXPATHLEN */
};

static int vnode_trace_path_callback(struct vnode *vp, void *arg) {
	int len, rv;
	struct vnode_trace_paths_context *ctx;

	ctx = arg;

	len = sizeof (ctx->path);
	rv = vn_getpath(vp, (char *)ctx->path, &len);
	/* vn_getpath() NUL-terminates, and len includes the NUL */

	if (!rv) {
		kdebug_lookup_gen_events(ctx->path, len, vp, TRUE);

		if (++(ctx->count) == 1000) {
			thread_yield_to_preemption();
			ctx->count = 0;
		}
	}

	return VNODE_RETURNED;
}

static int vfs_trace_paths_callback(mount_t mp, void *arg) {
	if (mp->mnt_flag & MNT_LOCAL)
		vnode_iterate(mp, VNODE_ITERATE_ALL, vnode_trace_path_callback, arg);

	return VFS_RETURNED;
}

static int sysctl_vfs_trace_paths SYSCTL_HANDLER_ARGS {
	struct vnode_trace_paths_context ctx;

	(void)oidp;
	(void)arg1;
	(void)arg2;
	(void)req;

	if (!kauth_cred_issuser(kauth_cred_get()))
		return EPERM;

	if (!kdebug_enable || !kdebug_debugid_enabled(VFS_LOOKUP))
		return EINVAL;

	bzero(&ctx, sizeof (struct vnode_trace_paths_context));

	vfs_iterate(0, vfs_trace_paths_callback, &ctx);

	return 0;
}

SYSCTL_PROC(_vfs_generic, OID_AUTO, trace_paths, CTLFLAG_RD | CTLFLAG_LOCKED | CTLFLAG_MASKED, NULL, 0, &sysctl_vfs_trace_paths, "-", "trace_paths");