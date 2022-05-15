#include <libgupnp/gupnp-root-device.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <signal.h>

GMainLoop *main_loop;

static void interrupt_signal_handler(int signum) {
        g_main_loop_quit(main_loop);
}
int main (int argc, char **argv) {
	struct sigaction sig_action;

	setlocale (LC_ALL, "");

	GError *error = NULL;
	GUPnPContext *context = g_initable_new(GUPNP_TYPE_CONTEXT, NULL, &error, NULL);

	if (error) {
		g_printerr("Error creating the GUPnP context: %s\n", error->message);
		g_error_free(error);
		return -1;
	}

	GUPnPRootDevice *dev = gupnp_root_device_new(context, "description.xml", ".");

	gupnp_root_device_set_available(dev, TRUE);

	main_loop = g_main_loop_new(NULL, FALSE);

	memset(&sig_action, 0, sizeof(sig_action));
	sig_action.sa_handler = interrupt_signal_handler;
	sigaction(SIGINT, &sig_action, NULL);

	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);

	g_object_unref(dev);
	g_object_unref(context);

	return 0;
}
