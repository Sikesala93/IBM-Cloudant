import os
from dotenv import load_dotenv
import requests
"""
IAM autentication values are retrieved from .env file
"""
load_dotenv()

IAM_LOGIN_URL = 'https://iam.cloud.ibm.com/identity/token?grant_type=urn:ibm:params:oauth:grant-type:apikey&apikey='
DATABASE = "sirq"

def login():
    # Login
    login_url = IAM_LOGIN_URL + os.environ.get('CLOUDANT_APIKEY')
    response = requests.post(login_url, data=None)
    print(response.json())
    return response.json()["access_token"]

# Post value
def post_value(token, value):
    url = f'{os.environ.get("CLOUDANT_URL")}/{DATABASE}'
    response = requests.post(url, json={
        "measure": value
    }, headers={
        'authorization': f'Bearer {token}',
    })
    print(response.json())
    return response.json()

def delete_value(token, document_id, rev):
    url = f'{os.environ.get("CLOUDANT_URL")}/{DATABASE}'
    url += f'{os.environ.get("CLOUDANT_URL")}/{DATABASE}/{document_id}?rev={rev}'
    print("DELETE HAPPENS")
    response = requests.delete(url, headers={
        'authorization': f'Bearer {token}',
    })
    print(response.json())



def get_all(token):
    url = f'{os.environ.get("CLOUDANT_URL")}/{DATABASE}/_all_docs'
    response = requests.get(url,headers={
        'authorization': f'Bearer {token}',
    })
    return response.json()

token = login()
#new_document = post_value(token=token, value=30)
#delete_value(token=token, document_id=new_document["id"], rev=new_document["rev"])
all_data = get_all(token=token)
print(all_data)
for data in all_data["rows"]:
    print(data)