/*
 *	$Id$
 *
 *	PCI defines and function prototypes
 *	Copyright 1994, Drew Eckhardt
 *	Copyright 1997, 1998 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *
 *	For more information, please consult the following manuals (look at
 *	http://www.pcisig.com/ for how to get them):
 *
 *	PCI BIOS Specification
 *	PCI Local Bus Specification
 *	PCI to PCI Bridge Specification
 *	PCI System Design Guide
 */

#ifndef BOOTLOADER_PCI_H
#define BOOTLOADER_PCI_H

#include <rtems/pci.h>


/* Functions used to access pci configuration space */
struct pci_bootloader_config_access_functions {
        int (*read_config_byte)(unsigned char, unsigned char,
                               unsigned char, unsigned char *);
        int (*read_config_word)(unsigned char, unsigned char,
                               unsigned char, unsigned short *);
        int (*read_config_dword)(unsigned char, unsigned char,
                               unsigned char, unsigned int *);
        int (*write_config_byte)(unsigned char, unsigned char,
                               unsigned char, unsigned char);
        int (*write_config_word)(unsigned char, unsigned char,
                               unsigned char, unsigned short);
        int (*write_config_dword)(unsigned char, unsigned char,
                               unsigned char, unsigned int);
};

/*
 * There is one pci_dev structure for each slot-number/function-number
 * combination:
 */
struct pci_dev {
	struct pci_bus	*bus;		/* bus this device is on */
	struct pci_dev	*sibling;	/* next device on this bus */
	struct pci_dev	*next;		/* chain of all devices */

	void		*sysdata;	/* hook for sys-specific extension */
	struct proc_dir_entry *procent;	/* device entry in /proc/bus/pci */

	unsigned int	devfn;		/* encoded device & function index */
	unsigned short	vendor;
	unsigned short	device;
	unsigned int	class;		/* 3 bytes: (base,sub,prog-if) */
	unsigned int	hdr_type;	/* PCI header type */
	unsigned int	master : 1;	/* set if device is master capable */
	/*
	 * In theory, the irq level can be read from configuration
	 * space and all would be fine.  However, old PCI chips don't
	 * support these registers and return 0 instead.  For example,
	 * the Vision864-P rev 0 chip can uses INTA, but returns 0 in
	 * the interrupt line and pin registers.  pci_init()
	 * initializes this field with the value at PCI_INTERRUPT_LINE
	 * and it is the job of pcibios_fixup() to change it if
	 * necessary.  The field must not be 0 unless the device
	 * cannot generate interrupts at all.
	 */
	unsigned int	irq;		/* irq generated by this device */

	/* Base registers for this device, can be adjusted by
	 * pcibios_fixup() as necessary.
	 */
	unsigned long	base_address[6];
	unsigned long	rom_address;
};

struct pci_bus {
	struct pci_bus	*parent;	/* parent bus this bridge is on */
	struct pci_bus	*children;	/* chain of P2P bridges on this bus */
	struct pci_bus	*next;		/* chain of all PCI buses */

	struct pci_dev	*self;		/* bridge device as seen by parent */
	struct pci_dev	*devices;	/* devices behind this bridge */

	void		*sysdata;	/* hook for sys-specific extension */
	struct proc_dir_entry *procdir;	/* directory entry in /proc/bus/pci */

	unsigned char	number;		/* bus number */
	unsigned char	primary;	/* number of primary bridge */
	unsigned char	secondary;	/* number of secondary bridge */
	unsigned char	subordinate;	/* max number of subordinate buses */
};

extern struct pci_bus	pci_root;	/* root bus */
extern struct pci_dev	*pci_devices;	/* list of all devices */

#endif /* BOOTLOADER_PCI_H */
