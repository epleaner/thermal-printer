require 'sinatra'
require 'securerandom'

get "/" do 
  `/usr/bin/lpr -PUSB_Thermal_Printer_LOCAL -o raw test.txt`
end

get "/print" do
  body = params[:text] + "\n\n\n"

  path = Tempfile.new(SecureRandom.hex).tap do |f|
    f.write(body)
    f.close
  end.path

  `/usr/bin/lpr -PUSB_Thermal_Printer_LOCAL -o raw #{path}`
end
