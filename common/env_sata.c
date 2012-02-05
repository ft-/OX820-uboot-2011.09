#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <sata.h>

/* references to names in env_common.c */
extern uchar default_environment[];

char *env_name_spec = "SATA";

env_t *env_ptr = 0;

DECLARE_GLOBAL_DATA_PTR;

uchar env_get_char_spec(int index)
{
	return (*((uchar *)(gd->env_addr + index)));
}

void env_relocate_spec(void)
{
	ulong buf[(CONFIG_ENV_SIZE + 511) / 128];
	unsigned int err, rc;

	err = init_sata(CONFIG_ENV_DEVICE);
	if (err) {
		set_default_env("!init_sata error");
		return;
	}

	err = sata_read(CONFIG_ENV_DEVICE, CONFIG_ENV_ADDR, CONFIG_ENV_SIZE, buf);
	if (err) {
		set_default_env("!sata_read error");
		return;
	}

	env_import(buf, 1);
}

int saveenv(void)
{
	unsigned int err;
	ulong buf[(CONFIG_ENV_SIZE + 511) / 128];
    memcpy(buf, env_ptr, CONFIG_ENV_SIZE);

	env_ptr->crc = crc32(0, env_ptr->data, ENV_SIZE);
	err = sata_write(CONFIG_ENV_DEVICE, CONFIG_ENV_ADDR, CONFIG_ENV_SIZE, buf);
	if (err)
		puts("*** Warning - sata_write error\n\n");

	return err;
}

int env_init(void)
{
	/* use default */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}
