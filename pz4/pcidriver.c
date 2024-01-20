#include <linux/pci.h>
#define DRV_NAME "megadriver"
#include <asm/io.h>
#include <linux/ioport.h>

unsigned int port_addr, port_len;

static struct pci_device_id rtl8169_pci_tbl[] = {       //PCI таблица
{0x10ec, 0x8168, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RTL8169}
};



MODULE_DEVICE_TABLE (pci, rtl8169_pci_tbl)             //Структура драйвера
static struct pci_driver rtl8169_pci_driver = {
	.name = DRV_NAME,
	.id_table = rtl8169_pci_tbl,
	.probe = rtl8169_init_one,
	.remove = rtl8169_remove_one,
};


int rtl8169_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	port_addr = pci_resource_start(dev,0); //начало области памяти
	port_len = pci_resource_len(dev,0);    //длина области памяти
	if (pci_resource_flags (dev,0)&IORESOURCE_MEM) //Проверка, что это память
	{
		printk ("OK.\n");
	}

	unsigned char* ptr = ioremap(port_addr,port_len); //перевод физического адреса в виртуальный
	for (int i=0; i<port_len;i++)
	{
		printk(KERN_INFO,"%x",(unsigned) ptr[i]);
	}

	major = register_chrdev(0,"MyPCI",&fops);
	printk(KERN_INFO "Load driver PCI %d\n",major);
	return 0;
}


void rtl8169_remove_one(struct pci_dev *dev)
{
	unregister_chrdev(major,"MyPCI");
}


static int rtl8169_init_module (void) {
	return pci_register_driver(&rtl8169_pci_driver);
}

void cleanup_module(void)
{
	pci_unregister_driver(&rtl8169_pci_driver);
}

