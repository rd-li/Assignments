from faker import Factory
fake = Factory.create()

states=['AA','AE','AP','AL','AK','AS','AZ','AR',
        'CA','CO','CT','DE','DC',
        'FL','GA','GU','HI','ID',
        'IL','IN','IA','KS','KY',
        'LA','ME','MD','MH','MA',
        'MI','FM','MN','MS','MO',
        'MT','NE','NJ','NV','NH','NM',
        'NY','NC','ND','MP','OH',
        'OK','OR','PW','PA','PR',
        'RI','SC','SD','TN','TX',
        'UT','VT','VA','VI','WA',
        'WV','WI','WY']

# data = []
outfile = open('outdata', 'wt')

for i in range(50000):
   name    = fake.name()
   address = fake.address()
   ccn = fake.ssn()
   phone = fake.phone_number()
   start = address.rfind(' ') + 1
   tail  = address[start:]
   address = address[:start-1]
   if '-' in tail:
       zipcode = tail[0:5]
   else:
       zipcode = tail
   # data.append( (name, address, zipcode) )
   address = address.replace('\n', ' ')
   state = address[-2:]
   if state not in states:
       print(state)
   if address[-4] == ',':
       address = address[:-4]
   else:
       address = address[:-3] 
   outfile.write( name + "|" + address + "|" + state + "|" + zipcode + "|" + phone + "|" + ccn + '\n' )

#  print( data )
outfile.close()


