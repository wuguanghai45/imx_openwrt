include $(TOPDIR)/rules.mk

PKG_NAME:=ecctest
PKG_RELEASE:=1

PKG_LICENSE:=GPL-2.0-or-later
PKG_MAINTAINER:=OpenWrt Developers <openwrt-devel@lists.openwrt.org>

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/ecctest
  SUBMENU:=Other modules
  TITLE:=ECC injection test module
  FILES:=$(PKG_BUILD_DIR)/ecctest.ko
  AUTOLOAD:=$(call AutoLoad,90,ecctest)
endef

define KernelPackage/ecctest/description
 Simple ECC error injection and detection test module.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	+$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,ecctest))
