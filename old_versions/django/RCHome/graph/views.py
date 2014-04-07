from django.shortcuts import render
from django.template import RequestContext, loader
from django.http import HttpResponse

from graph.models import SensorBoard1, CommandTable

def index(request):
    latest_sensors_list = SensorBoard1.objects.order_by('-datetime')[:60]
    latest_sensor=latest_sensors_list[0]
    try:
     pk=request.POST['led']
    except (KeyError, SensorBoard1.DoesNotExist):
      pk=latest_sensor.led
    led_stat=pk
    if not(led_stat == latest_sensor.led):
      command=CommandTable(result9=led_stat)
      latest_sensor.led = led_stat
      command.save()
    short_sensor_list=list()
    for i in xrange(0,60,10):
      short_sensor_list.append(latest_sensors_list[i])
    short_sensor_list.reverse()
    template = loader.get_template('index.html')
    context = RequestContext(request, {'short_sensor_list': short_sensor_list, 'last_value':latest_sensor,})
    
    
      
    
    
    
    
    
    
    
    
    return HttpResponse(template.render(context))