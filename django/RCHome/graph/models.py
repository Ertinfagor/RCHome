from django.db import models
import datetime

class SensorBoard(models.Model):
    address = models.BigIntegerField()
    datetime = models.DateTimeField(primary_key=True)
    Command = models.SmallIntegerField()
    Command_result = models.SmallIntegerField() 
    Temperature = models.SmallIntegerField() 
    Humidity = models.SmallIntegerField()
    value7 = models.SmallIntegerField()
    value8 = models.SmallIntegerField()
    value9 = models.SmallIntegerField()
    value10 = models.SmallIntegerField()
    value11 = models.SmallIntegerField()
    value12 = models.SmallIntegerField()
    led = models.SmallIntegerField()
    value14 = models.SmallIntegerField()
    value15 = models.SmallIntegerField()
    value16 = models.SmallIntegerField()
    value17 = models.SmallIntegerField()
    value18 = models.SmallIntegerField()
    value19 = models.SmallIntegerField()
    value20 = models.SmallIntegerField()
    value21 = models.SmallIntegerField()
    value22 = models.SmallIntegerField()
    value23 = models.SmallIntegerField()
    value24 = models.SmallIntegerField()
    value25 = models.SmallIntegerField()
    value26 = models.SmallIntegerField()
    value27 = models.SmallIntegerField()
    value28 = models.SmallIntegerField()
    value29 = models.SmallIntegerField()
    value30 = models.SmallIntegerField()
    value31 = models.SmallIntegerField()
    value32 = models.SmallIntegerField()
    value33 = models.SmallIntegerField()
    value34 = models.SmallIntegerField()
    
    def __str__(self):
      return self.datetime.strftime("%Y-%m-%d %H:%M:%S")
    class Meta:
      abstract = True
      
      
class CommandTable(models.Model):
    id=models.AutoField(primary_key=True)
    time = models.DateTimeField(auto_now_add=True)
    priority = models.SmallIntegerField(default=1)
    address = models.BigIntegerField(default=1034834472962)
    command = models.SmallIntegerField(default=1)
    command_result = models.SmallIntegerField(blank=True,default=0) 
    result1 = models.SmallIntegerField(blank=True,default=1) 
    result2 = models.SmallIntegerField(blank=True,default=1)
    result3 = models.SmallIntegerField(blank=True,default=1)
    result4 = models.SmallIntegerField(blank=True,default=1)
    result5 = models.SmallIntegerField(blank=True,default=1)
    result6 = models.SmallIntegerField(blank=True,default=1)
    result7 = models.SmallIntegerField(blank=True,default=1)
    result8 = models.SmallIntegerField(blank=True,default=1)
    result9 = models.SmallIntegerField("LED",blank=True,default=0)
    result10 = models.SmallIntegerField(blank=True,default=1)
    result11 = models.SmallIntegerField(blank=True,default=1)
    result12 = models.SmallIntegerField(blank=True,default=1)
    result13 = models.SmallIntegerField(blank=True,default=1)
    result14 = models.SmallIntegerField(blank=True,default=1)
    result15 = models.SmallIntegerField(blank=True,default=1)
    result16 = models.SmallIntegerField(blank=True,default=1)
    result17 = models.SmallIntegerField(blank=True,default=1)
    result18 = models.SmallIntegerField(blank=True,default=1)
    result19 = models.SmallIntegerField(blank=True,default=1)
    result20 = models.SmallIntegerField(blank=True,default=1)
    result21 = models.SmallIntegerField(blank=True,default=1)
    result22 = models.SmallIntegerField(blank=True,default=1)
    result23 = models.SmallIntegerField(blank=True,default=1)
    result24 = models.SmallIntegerField(blank=True,default=1)
    result25 = models.SmallIntegerField(blank=True,default=1)
    result26 = models.SmallIntegerField(blank=True,default=1)
    class Meta:
      managed=False
      db_table = 'commands_test'
    
    def __str__(self):
      return 'command'
    
class SensorBoard1(SensorBoard):
    class Meta:
      managed=False
      db_table = '1034834472962'
      
      
