
/*lint --e{537} */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <bsp_reset.h>
#ifdef CONFIG_BALONG_MODEM_RESET
#include <linux/huawei/rdr.h>
#else  /* !CONFIG_BALONG_MODEM_RESET */
#ifndef hisi_system_error
static inline void hisi_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
	printk("[reset]: <%s> is stub\n", __FUNCTION__);
	return;
}
#endif
#endif /* CONFIG_BALONG_MODEM_RESET */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_BALONG_MODEM_BOOT)

struct balong_power_plat_data {
    u32 modem_state;
};

enum modem_state_index {
    MODEM_NOT_READY = 0,
    MODEM_READY,
    MODEM_INVALID,
};

static struct balong_power_plat_data* balong_driver_plat_data = NULL;
static const char* const modem_state_str[] = {
    "MODEM_STATE_OFF\n",
    "MODEM_STATE_READY\n",
    "MODEM_STATE_INVALID\n",
};
/*To make modem poweroff called only once when there are two rilds.*/
static int modem_power_off_flag = 0;

#ifndef HISI_RDR_MOD_CP_RILD
#define HISI_RDR_MOD_CP_RILD 0x82000007
#endif
#ifndef HISI_RDR_MOD_CP_3RD
#define HISI_RDR_MOD_CP_3RD  0x82000008
#endif

int  cry_state = 0;

/*****************************************************************************
 函 数 名  : modem_state_set
 功能描述  : 提供ttf设置modem状态的API
 输入参数  : unsigned int state
 输出参数  : 无
 返 回 值  : <0     failed,invalid state
             =0     success
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    作    者   : 陈易超
    修改内容   : 新生成函数

*****************************************************************************/
int modem_state_set(unsigned int state)
{
    if (!balong_driver_plat_data){
        printk("Balong_power %s:%d not init.\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }
    if (state >= MODEM_INVALID){
        printk("Balong_power %s:%d invalid state 0x%x.\n", __FUNCTION__, __LINE__, state);
        return -EINVAL;
    }

    balong_driver_plat_data->modem_state = state;

    return 0;
}

static ssize_t balong_power_get(struct device *dev, struct device_attribute *attr, char *buf)
{
    ssize_t len;

    if (!balong_driver_plat_data) {
        printk(KERN_ERR"Balong_power %s:%d not init.\n", __FUNCTION__, __LINE__);
        return 0;
    }
    if (balong_driver_plat_data->modem_state >= MODEM_INVALID){
        printk(KERN_ERR"Balong_power : %s:%d Invalid state 0x%x now is set.\n", __FUNCTION__, __LINE__, balong_driver_plat_data->modem_state);
        return 0;
    }

    len = snprintf(buf, strlen(modem_state_str[balong_driver_plat_data->modem_state]) + 1,
        "%s\n", modem_state_str[balong_driver_plat_data->modem_state]);

    return len;
}

ssize_t modem_reset_set(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int state;
	char* endp;
	if (!bsp_reset_is_connect_ril())
	{
		pr_err("<modem_reset_set>: modem reset not to be connected to ril\n");
		return count;
	}
	dev_info(dev, "Power set to %s\n", buf);
	state = simple_strtol(buf, &endp, 10); /*10 means read as dec*/
	pr_err("endp = 0x%x\n", *(int*)endp);
	pr_err("count = %lu\n", (unsigned long)count);
	if (*buf == '\0' || *buf == *endp)/* return 0 means match failed */
	{
		return count;
	}
	if (state == BALONG_MODEM_RESET)
	{
		hisi_system_error(HISI_RDR_MOD_CP_REBOOT, 0, 0, NULL, 0);
		pr_err("modem reset %d\n", BALONG_MODEM_RESET);
		return count;
	}
	else if(state == BALONG_MODEM_OFF)
	{
		/*To make modem poweroff called only once when there are two rilds.*/
		if(modem_power_off_flag)
		{
			pr_err("Balong_power: modem power off has been called! \n");
			return count;
		}
		bsp_modem_power_off();
		pr_err("modem power off %d\n", BALONG_MODEM_OFF);
		modem_power_off_flag = 1;
		return count;
	}
	else if(state == BALONG_MODEM_ON) /* TODO: 是否需要上电，根HIFI什么关系 */
	{
		bsp_modem_power_on();
		pr_err("modem power on %d\n", BALONG_MODEM_ON);
	}
	else if(state == BALONG_MODEM_RILD_SYS_ERR)
	{
		hisi_system_error(HISI_RDR_MOD_CP_RILD, 0, 0, NULL, 0);
		pr_err("modem reset using hisi_system_error by rild %d\n", BALONG_MODEM_RILD_SYS_ERR);
	}
	else if(state == BALONG_MODEM_3RD_SYS_ERR)
	{
		hisi_system_error(HISI_RDR_MOD_CP_3RD, 0, 0, NULL, 0);
		pr_err("modem reset using hisi_system_error by 3rd modem %d\n", HISI_RDR_MOD_CP_3RD);
	}
	else
	{
		pr_err("Balong_power : invalid code to balong power !!!!\n");
		return count;
	}
	return count;

}

ssize_t modem_state_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    return count;
}

static DEVICE_ATTR(state, 0660, balong_power_get, modem_reset_set);

ssize_t cryptfs_state_get(struct device *dev, struct device_attribute *attr, char *buf)
{
       return sprintf(buf, "%d\n", cry_state);
}

ssize_t cryptfs_state_set(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
        int mode, ret;

        ret = kstrtoint(buf, 10, &mode);
        if (ret)
        {
                printk("set cryptfs state failed,mode = %d\n",mode);
                return ret;
        }
        cry_state = mode ;
	return count;
}

static DEVICE_ATTR(cryptfs_state, 0660, cryptfs_state_get, cryptfs_state_set);

static DEVICE_ATTR(modem_state, 0660, balong_power_get, modem_state_write);

static int __init bsp_power_probe(struct platform_device *pdev)
{
    int ret = 0;
  
    cry_state = 0;

    balong_driver_plat_data = pdev->dev.platform_data;

    ret |= device_create_file(&(pdev->dev), &dev_attr_state);
    ret |= device_create_file(&(pdev->dev), &dev_attr_modem_state);

    ret |= device_create_file(&(pdev->dev), &dev_attr_cryptfs_state);
    if (ret)
    {
        printk("fail to creat modem boot sysfs\n");
        return ret;
    }

    return ret;
}

static struct balong_power_plat_data  balong_power_plat_data = {
    .modem_state = MODEM_NOT_READY,
};

static struct platform_device balong_power_device = {
    .name = "balong_power",
    .id = -1,
    .dev = {
        .platform_data = &balong_power_plat_data,
    },
};

static struct platform_driver balong_power_drv = {
    .probe      = bsp_power_probe,
    .driver     = {
        .name     = "balong_power",
        .owner    = THIS_MODULE,
    },
};

static int bsp_modem_boot_init(void);
static void bsp_modem_boot_exit(void);

static int __init bsp_modem_boot_init(void)
{
    int ret = 0;

    ret = platform_device_register(&balong_power_device);
    if(ret)
    {
        printk("register his_modem boot device failed. \r\n");
        return ret;
    }

    ret = platform_driver_register(&balong_power_drv);
    if(ret)
    {
        printk("register his_modem boot driver failed. \r\n");
        platform_device_unregister(&balong_power_device);
    }

    return ret;
}

static void __exit bsp_modem_boot_exit(void)
{
    platform_driver_unregister(&balong_power_drv);
    platform_device_unregister(&balong_power_device);
}

module_init(bsp_modem_boot_init);
module_exit(bsp_modem_boot_exit);

MODULE_AUTHOR("z00227143@huawei.com");
MODULE_DESCRIPTION("HIS Balong Modem boot");
MODULE_LICENSE("GPL");

#else /* stub */

#endif

#ifdef __cplusplus
}
#endif

