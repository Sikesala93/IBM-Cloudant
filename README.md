
# Cloudant-yhteys

## Kokeile

Lisää omat IAM-kirjautumistiedot .env.example tiedoston perusteella. https://pypi.org/project/python-dotenv/

## Linkkejä

    # Jos käytät python requests-kirjastoa
    https://cloud.ibm.com/apidocs/cloudant
    https://cloud.ibm.com/apidocs/iam-identity-token-api
    
    # Jos käytät cloudant python sdk:ta
    https://github.com/IBM/cloudant-python-sdk
    https://cloud.ibm.com/apidocs/cloudant?code=python
    https://cloud.ibm.com/apidocs/cloudant?code=python#postalldocs

## Tehtävät

 1. Muodosta yhteys cloudant-tietokantaan. Luo funktiot dokumentin tallentamiselle, poistamiselle ja kaikkien tallennettujen dokumenttien hakemiselle 
 2. Tee IBM-watson-mqtt-rajapinta-client cloudantin käyttämiselle. lähettämällä json-objektin mqtt:lle, ohjelma vastaanottaa sen ja tallentaa cloudant-tietokantaan

## Lisätehtävät

 2. Kerää dataa kahdesta kuvitteellisesta/todellisesta anturista. Koosta niistä yhteinen dokumentti/json, jonka vasta sitten tallennat cloudant-tietokantaan
