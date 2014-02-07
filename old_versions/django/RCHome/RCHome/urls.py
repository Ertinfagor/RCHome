from django.conf.urls import patterns, include, url

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'RCHome.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),
    url(r'^graph/', include('graph.urls')),
    url(r'^admin/', include(admin.site.urls)),
)
