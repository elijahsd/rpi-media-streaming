#include <libgupnp/gupnp-control-point.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <signal.h>
#include <glib.h>

GMainLoop *main_loop;

static void interrupt_signal_handler(G_GNUC_UNUSED int signum) {
	g_main_loop_quit(main_loop);
}

static void device_proxy_available_cb(G_GNUC_UNUSED GUPnPControlPoint *cp,
		GUPnPDeviceProxy *proxy) {
	const char *type = gupnp_device_info_get_device_type(GUPNP_DEVICE_INFO(proxy));

	if (!strcmp(type, "urn:schemas-iridiumrain-net:device:MediaPlayer:1")) {
		char *name = gupnp_device_info_get_friendly_name(GUPNP_DEVICE_INFO(proxy));
	}
}

static void device_proxy_unavailable_cb(G_GNUC_UNUSED GUPnPControlPoint *cp,
		GUPnPDeviceProxy *proxy) {
	const char *type = gupnp_device_info_get_device_type(GUPNP_DEVICE_INFO(proxy));

	if (!strcmp(type, "urn:schemas-iridiumrain-net:device:MediaPlayer:1")) {
		char *name = gupnp_device_info_get_friendly_name(GUPNP_DEVICE_INFO(proxy));
	}
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

	GUPnPControlPoint *cp = gupnp_control_point_new(context, "ssdp:all");

	g_signal_connect(cp, "device-proxy-available", G_CALLBACK(device_proxy_available_cb), NULL);
	g_signal_connect(cp, "device-proxy-unavailable", G_CALLBACK(device_proxy_unavailable_cb), NULL);

	gssdp_resource_browser_set_active(GSSDP_RESOURCE_BROWSER(cp), TRUE);

	main_loop = g_main_loop_new(NULL, FALSE);

	memset(&sig_action, 0, sizeof(sig_action));
	sig_action.sa_handler = interrupt_signal_handler;
	sigaction(SIGINT, &sig_action, NULL);

	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);

	g_object_unref(cp);
	g_object_unref(context);

	return 0;
}
